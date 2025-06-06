#include "orbsvcs/Log_Macros.h"
#include "tao_imr_i.h"

#include "tao/PortableServer/PortableServer.h"
#include "tao/PortableServer/ForwardRequestC.h"

#include "tao/Stub.h"
#include "tao/Profile.h"
#include "ace/Get_Opt.h"
#include "ace/Read_Buffer.h"
#include "ace/OS_NS_strings.h"
#include "ace/os_include/os_netdb.h"
#include "ace/OS_NS_unistd.h"

TAO_IMR_i::TAO_IMR_i ()
  : argc_ (0),
    argv_ (0),
    orb_ (),
    imr_ (ImplementationRepository::Administration::_nil ()),
    op_ ()
{
  // Nothing
}

TAO_IMR_i::~TAO_IMR_i ()
{
}

int
TAO_IMR_i::run ()
{
  if (this->op_.get () == 0)
    {
      ORBSVCS_ERROR ((LM_ERROR, "Unknown operation"));
      return TAO_IMR_Op::UNKNOWN;
    }

  return this->op_->run ();
}

int
TAO_IMR_i::init (int argc, ACE_TCHAR **argv)
{
  this->argc_ = argc;
  this->argv_ = argv;

  const char *exception_message = "Null Message";

  try
    {
      // Retrieve the ORB.
      this->orb_ = CORBA::ORB_init (this->argc_, this->argv_, "tao_imr_i");

      // Parse command line and verify parameters.
      if (this->parse_args () == -1)
        return -1;

      // Get the ImplRepo object
      CORBA::Object_var obj =
        orb_->resolve_initial_references ("ImplRepoService");

      if (CORBA::is_nil (obj.in ()))
        {
          ORBSVCS_ERROR ((LM_ERROR, "Unable to resolve the ImR.\n"));
          return -1;
        }

      exception_message = "While narrowing ImR";

      this->imr_ =
        ImplementationRepository::Administration::_narrow (obj.in ());

      if (CORBA::is_nil (imr_.in ()))
        {
          ORBSVCS_ERROR ((LM_ERROR, "Unable to narrow the ImR.\n"));
          return -1;
        }

      this->op_->set_imr (this->imr_.in ());
    }
  catch (const CORBA::Exception& ex)
    {
      ORBSVCS_ERROR ((LM_ERROR, "TAO_IMR_i::init - %C\n", exception_message));
      ex._tao_print_exception ("Exception");
      return -1;
    }

  return 0;
}


// Go through and figure out which operation we should do.

int
TAO_IMR_i::parse_args ()
{
  // Make sure one command was given
  if (this->argc_ < 2)
    {
      ORBSVCS_ERROR((LM_ERROR, "Error: No operation specified.\n"));
      this->print_usage ();
      return -1;
    }

  this->op_.reset (TAO_IMR_Op::make_op (this->argv_[1]));

  // Check for unrecognized operation

  if (this->op_.get () == 0)
    {
      ORBSVCS_ERROR((LM_ERROR, "Error: Unknown operation '%s'.\n", this->argv_[1]));
      this->print_usage ();
      return -1;
    }

  // Adjust argc and argv so only the command specific args are passed
  return this->op_->parse (this->argc_ - 1, this->argv_ + 1);
}


// Print out information about all operations.

void
TAO_IMR_i::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR, "Usage: tao_imr [options] command [command-arguments]\n"
    "  where [options] are ORB options\n"
    "  where command is one of the following:\n"
    "    start         Start a server through the ImR\n"
    "    add           Add an entry to the ImR\n"
    "    autostart     Activates all AUTO_START servers\n"
    "    ior           Creates a simplified IOR\n"
    "    list          List the entries in the ImR\n"
    "    remove        Remove an entry from the ImR\n"
    "    shutdown      Shut down a server through the ImR\n"
    "    shutdown-repo Shut down the ImR\n"
    "    update        Update an entry in the ImR\n"
    "  where [command-arguments] depend on the command\n"));
}


// Factory for operations

TAO_IMR_Op *
TAO_IMR_Op::make_op (const ACE_TCHAR *op_name)
{
  if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("activate")) == 0)
    {
      ORBSVCS_ERROR((LM_ERROR, "Warning: The activate option has been renamed to start.\n"));
      return new TAO_IMR_Op_Activate ();
    }
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("start")) == 0)
    return new TAO_IMR_Op_Activate ();
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("add")) == 0)
    return new TAO_IMR_Op_Register (true);
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("autostart")) == 0)
    return new TAO_IMR_Op_Autostart();
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("ior")) == 0)
    return new TAO_IMR_Op_IOR();
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("kill")) == 0)
    return new TAO_IMR_Op_Kill ();
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("link")) == 0)
    return new TAO_IMR_Op_Link ();
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("list")) == 0)
    return new TAO_IMR_Op_List ();
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("remove")) == 0)
    return new TAO_IMR_Op_Remove ();
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("shutdown")) == 0)
    return new TAO_IMR_Op_Shutdown ();
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("shutdown-repo")) == 0)
    return new TAO_IMR_Op_ShutdownRepo ();
  else if (ACE_OS::strcasecmp (op_name, ACE_TEXT ("update")) == 0)
    return new TAO_IMR_Op_Register (false);

  return 0;
}


TAO_IMR_Op::~TAO_IMR_Op ()
{
  // Nothing
}

void
TAO_IMR_Op::set_imr (ImplementationRepository::Administration_ptr imr)
{
  this->imr_ = imr;
}

void
TAO_IMR_Op::display_server_information (const ImplementationRepository::ServerInformation &info)
{
  // Figure out what the activation string is.
  const char *act = "UNKNOWN STARTUP";
  if (info.startup.activation == ImplementationRepository::NORMAL)
    act = "NORMAL";
  else if (info.startup.activation == ImplementationRepository::MANUAL)
    act = "MANUAL";
  else if (info.startup.activation == ImplementationRepository::PER_CLIENT)
    act = "PER_CLIENT";
  else if (info.startup.activation == ImplementationRepository::AUTO_START)
    act = "AUTO_START";

  // Print out information
  ORBSVCS_DEBUG ((LM_DEBUG, "Server <%C>\n", info.server.in ()));

  const char * locked_out = "";

  int limit = info.startup.start_limit;
  if (info.startup.start_limit < 0)
    {
      limit = -limit;
      locked_out = "  Locked Out\n";
    }

  ORBSVCS_DEBUG ((LM_DEBUG, "  Activator: %C\n", info.startup.activator.in ()));

  ORBSVCS_DEBUG ((LM_DEBUG, "  Command Line: "));
  if (ACE_OS::strlen(info.startup.command_line.in ()) <= ACE_MAXLOGMSGLEN)
    {
       ORBSVCS_DEBUG ((LM_DEBUG, "%C", info.startup.command_line.in ()));
    }
  else
    {
       char *cl = const_cast<char *>(info.startup.command_line.in ());
       while (*cl)
         {
            char tmp = 0;
            size_t len = ACE_OS::strlen(cl);
            if (len > ACE_MAXLOGMSGLEN)
              {
                 len = ACE_MAXLOGMSGLEN;
                 tmp = cl[len+1];
                 cl[len+1] = 0;
              }
            ORBSVCS_DEBUG ((LM_DEBUG, "%C", cl));
            cl[len+1] = tmp;
            cl += len;
         }
    }
  ORBSVCS_DEBUG ((LM_DEBUG, "\n"));
  ORBSVCS_DEBUG ((LM_DEBUG, "  Working Directory: %s\n", info.startup.working_directory.in ()));
  ORBSVCS_DEBUG ((LM_DEBUG, "  Activation Mode: %C\n", act));
  ORBSVCS_DEBUG ((LM_DEBUG, "  Number of retries: %d\n%C", limit - 1, locked_out));


  for (CORBA::ULong i = 0; i < info.startup.environment.length (); ++i)
    ORBSVCS_DEBUG ((LM_DEBUG, "Environment Variable: %C=%C\n",
    info.startup.environment[i].name.in (),
    info.startup.environment[i].value.in ()));

  if (info.startup.activation == ImplementationRepository::PER_CLIENT)
    ORBSVCS_DEBUG ((LM_DEBUG,
                "  No running info available for PER_CLIENT mode\n"));
  else if (ACE_OS::strlen (info.partial_ior.in ()) > 0)
    ORBSVCS_DEBUG ((LM_DEBUG,
                "  Running at endpoint: %C\n",
                info.partial_ior.in ()));
  else   // I am assuming that a blank partial_ior means currently not running.
    ORBSVCS_DEBUG ((LM_DEBUG,
                "  Not currently running\n"));

  ORBSVCS_DEBUG ((LM_DEBUG, "\n"));
}

TAO_IMR_Op_List::TAO_IMR_Op_List ()
: verbose_server_information_ (0)
, list_only_active_servers_ (0)
, how_many_ (0)
, terse_ (0)
{
  // Nothing
}

TAO_IMR_Op_Register::TAO_IMR_Op_Register (bool is_add)
: is_add_ (is_add)
, set_command_line_ (false)
, set_environment_vars_(false)
, set_working_dir_ (false)
, set_activation_ (false)
, activation_(ImplementationRepository::NORMAL)
, set_retry_count_(false)
, retry_count_ (0)
, set_activator_ (false)
{
  // Nothing
}

void
TAO_IMR_Op_Activate::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR,
                  "Starts a server using its registered Activator.\n\n"
                  "Usage: tao_imr [options] start <name>\n"
                  "  where [options] are ORB options\n"
                  "  where <name> is the name of a registered POA.\n"
                  "  -q run quietly\n"
                  "  -h Displays this\n"));
}

int
TAO_IMR_Op_Activate::parse (int argc, ACE_TCHAR **argv)
{
  // Check for enough arguments (we need at least one for the server name)
  if (argc < 2)
    {
      this->print_usage ();
      return -1;
    }

  // Skip both the program name and the "activate" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("hq"));

  this->server_name_ = ACE_TEXT_ALWAYS_CHAR(argv[1]);
  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 'q' :
        this->quiet_ = true;
        break;
      case 'h':
        this->print_usage ();
        return -1;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }
  return 0;
}

void
TAO_IMR_Op_Autostart::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR, "Usage: tao_imr [options] autostart\n"
    "  where [options] are ORB options\n"
    "  -h Displays this\n"));
}

int
TAO_IMR_Op_Autostart::parse (int argc, ACE_TCHAR **argv)
{
  // Skip the "autostart" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("h"));

  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 'h':  // display help
        this->print_usage ();
        return -1;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }
  return 0;
}

void
TAO_IMR_Op_IOR::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR, "Creates an IOR for a server that is registered with the IMR and uses\n"
    "the InterOperable Naming Service.  Please see the documentation for\n"
    "more information on which server configurations work with this command.\n"
    "\n"
    "Usage: tao_imr [options] ior <object_key> [command-arguments]\n"
    "  where [options] are ORB options\n"
    "  where <object_key> matches the simple key bound in the server IORTable.\n"
    "  where [command-arguments] can be\n"
    "    -f filename   filename to output the IOR to\n"
    "    -h            Displays this\n"));
}

int
TAO_IMR_Op_IOR::parse (int argc, ACE_TCHAR **argv)
{
  // Check for enough arguments (we need at least one for the server name)
  if (argc < 2)
    {
      this->print_usage ();
      return -1;
    }

  // Skip both the program name and the "ior" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("hf:"));

  this->server_name_ = ACE_TEXT_ALWAYS_CHAR(argv[1]);
  if (this->server_name_.length() == 0 || this->server_name_[0] == '-')
    {
      ORBSVCS_ERROR((LM_ERROR, "ERROR : name is required.\n"));
      this->print_usage ();
      return -1;
    }

  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 'f':  // File name
        this->filename_ = get_opts.opt_arg ();
        break;
      case 'h':  // display help
        this->print_usage ();
        return -1;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }
  return 0;
}

void
TAO_IMR_Op_Kill::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR,
                  "Sends a signal to the designated process\n\n"
                  "The process must have been started by the ImR\n"
                  "and may not use per-client activation\n"
                  "Usage: tao_imr [options] kill [name] [command-arguments]\n"
                  "  where [options] are ORB options\n"
                  "  where [name] is the registered POA name the peers link to\n"
                  "  where [command-arguments] can be\n"
                  "    -q run quietly\n"
                  "    -s signum   default 9, the signal to be sent to the\n"
                  "                process for named server\n"));
}

int
TAO_IMR_Op_Kill::parse (int argc, ACE_TCHAR **argv)
{
  int server_flag = 0;

  if (argc > 1 && argv[1][0] != '-')
  {
    this->server_name_ = ACE_TEXT_ALWAYS_CHAR(argv[1]);
    server_flag = 2;
  }
  this->signum_ = 9;

  // Skip both the program name and the "list" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("s:hq"), server_flag);

  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 's': //signum
        this->signum_ = ACE_OS::strtol (get_opts.opt_arg (), 0, 10);
        break;
      case 'q' :
        this->quiet_ = true;
        break;
      case 'h':  // display help
        this->print_usage ();
        return -1;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }
  return 0;
}

void
TAO_IMR_Op_Link::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR, "Links multiple POAs to a single executable\n"
    "\n"
    "Usage: tao_imr [options] link [name] [command-arguments]\n"
    "  where [options] are ORB options\n"
    "  where [name] is the registered POA name the peers link to\n"
    "  where [command-arguments] can be\n"
    "    -p peers    provides a comma separated list of additional POAs that are\n"
    "                part of the same executable. -p may be repeated\n"));
}

int
TAO_IMR_Op_Link::parse (int argc, ACE_TCHAR **argv)
{
  int server_flag = 0;

  if (argc > 1 && argv[1][0] != '-')
  {
    this->server_name_ = ACE_TEXT_ALWAYS_CHAR(argv[1]);
    server_flag = 2;
  }

  // Skip both the program name and the "list" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("p:h"), server_flag);

  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 'p': //list of peers
        {
          char *arg = ACE_TEXT_ALWAYS_CHAR (get_opts.opt_arg ());
          CORBA::ULong last = this->peers_.length ();
          CORBA::ULong num = 0;
          char *c2 = arg;
          while (c2 != 0)
            {
              num++;
              c2 = ACE_OS::strchr (c2, ',');
              if (c2 != 0)
                c2++;
            }
          num += last;
          this->peers_.length (num);
          while (last < num)
            {
              if ((c2 = ACE_OS::strchr (arg, ',')) != 0)
                *c2 = 0;
              this->peers_[last++] = CORBA::string_dup (arg);
              if (c2 != 0)
                arg = c2+1;
            }
          break;
        }
      case 'h':  // display help
        this->print_usage ();
        return -1;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }
  return 0;
}

void
TAO_IMR_Op_List::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR, "Lists all or one of the servers in the Implementation Repository\n"
    "\n"
    "Usage: tao_imr [options] list [name] [command-arguments]\n"
    "  where [options] are ORB options\n"
    "  where [name] is the optional server name to search for\n"
    "  where [command-arguments] can be\n"
    "    -v            Verbose: Displays more info for each server when\n"
    "                  displaying more than one server\n"
    "    -a            List only servers that are determined to be active\n"
    "    -n <count>    Request no more than <count> entries and use an iterator\n"
    "    -h            Displays this\n"));
}

int
TAO_IMR_Op_List::parse (int argc, ACE_TCHAR **argv)
{
  int server_flag = 0;

  if (argc > 1 && argv[1][0] != '-')
  {
    this->server_name_ = ACE_TEXT_ALWAYS_CHAR(argv[1]);
    server_flag = 2;
  }

  // Skip both the program name and the "list" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("ahn:tv"), server_flag);

  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 'v': // verbose server display
        this->verbose_server_information_ = 1;
        break;
      case 't':
        this->terse_ = 1;
        break;
      case 'a':
        this->list_only_active_servers_ = 1;
        break;
      case 'n':
        this->how_many_ = ACE_OS::atoi (get_opts.opt_arg ());
        break;
      case 'h':  // display help
        this->print_usage ();
        return -1;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }
  return 0;
}

void
TAO_IMR_Op_Remove::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR, "Removes a server entry\n"
    "\n"
    "Usage: tao_imr [options] remove <name> [-f [-s <signum>]]\n"
    "  where [options] are ORB options\n"
    "  -f forces shutdown or kill of a running server"
    "  -s specifies a signal for killing the server, if it is 0, a shutdown will be used"
    "  where <name> is the POA name used by the server object\n"
    "  -h Displays this\n"));
}

int
TAO_IMR_Op_Remove::parse (int argc, ACE_TCHAR **argv)
{
  // Check for enough arguments (we need at least one for the server name)
  if (argc < 2)
    {
      this->print_usage ();
      return -1;
    }
  this->force_ = false;
  this->signum_ = 0;

  // Skip both the program name and the "remove" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("hfs:"));

  this->server_name_ = ACE_TEXT_ALWAYS_CHAR(argv[1]);
  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 'h':
        this->print_usage ();
        return -1;
      case 'f':
        this->force_ = true;
        break;
      case 's':
        this->signum_ = ACE_OS::strtol (get_opts.opt_arg (), 0, 10);
        break;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }

  return 0;
}

void
TAO_IMR_Op_Shutdown::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR,
                  "Shuts down a server\n\n"
                  "Usage: tao_imr [options] shutdown <name>\n"
                  "  where [options] are ORB options\n"
                  "  where <name> is the name of the server object\n"
                  "  -q run quietly\n"
                  "  -h Displays this\n"));
}

int
TAO_IMR_Op_Shutdown::parse (int argc, ACE_TCHAR **argv)
{
  // Check for enough arguments (we need at least one for the server name)
  if (argc < 2)
    {
      this->print_usage ();
      return -1;
    }

  // Skip both the program name and the "shutdown" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("hq"));

  this->server_name_ = ACE_TEXT_ALWAYS_CHAR(argv[1]);
  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 'q' :
        this->quiet_ = true;
        break;
      case 'h':
        this->print_usage ();
        return -1;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }
  return 0;
}

TAO_IMR_Op_ShutdownRepo::TAO_IMR_Op_ShutdownRepo()
: activators_(false)
{
}

void
TAO_IMR_Op_ShutdownRepo::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR, "Shuts down the ImR\n"
    "\n"
    "Usage: tao_imr [options] shutdown-repo [-a]\n"
    "  where [options] are ORB options\n"
    "  Specify -a to also shutdown any registered ImR Activators.\n"
    "  -h Displays this\n"));
}

int
TAO_IMR_Op_ShutdownRepo::parse (int argc, ACE_TCHAR **argv)
{
  // Check for enough arguments (we need at least one for the server name)
  if (argc < 1)
    {
      this->print_usage ();
      return -1;
    }

  // Skip both the program name and the "shutdown-repo" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("ha"));

  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 'h':
        this->print_usage ();
        return -1;
      case 'a':
        activators_ = true;
        break;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }

  return 0;
}

void
TAO_IMR_Op_Register::addenv (ACE_TCHAR *opt)
{
  CORBA::ULong length = this->environment_vars_.length ();
  // Increase the length of the sequence
  this->environment_vars_.length (length + 1);
  ACE_TString tokens (opt);
  size_t index = tokens.find (ACE_TEXT("="));
  // Insert at position length since that is our new element
  this->environment_vars_ [length].name =
    CORBA::string_dup (ACE_TEXT_ALWAYS_CHAR(tokens.substr (0, index).c_str ()));
  this->environment_vars_ [length].value =
    CORBA::string_dup (ACE_TEXT_ALWAYS_CHAR(tokens.substr (index + 1).c_str ()));
}

void
TAO_IMR_Op_Register::print_usage ()
{
  ORBSVCS_ERROR ((LM_ERROR,
    "Adds/Updates a server entry\n\n"
    "Usage: tao_imr [options] <add|update> <name> [command-arguments]\n"
    "  where [options] are ORB options\n"
    "  where <name> is the POA name used by the server object\n"
    "  where [command-arguments] can be\n"
    "    -h            Displays this\n"
    "    -q            run quietly\n"
    "    -l            Activator name.\n"
    "    -c command    Startup command\n"
    "    -w dir        Working directory\n"
    "    -e name=value Set environment variables\n"
    "    -a mode       Set activate mode (NORMAL|MANUAL|PER_CLIENT|AUTO_START)\n"
    "    -r count      Set the startup/ping retry count to count\n"));
}

int
TAO_IMR_Op_Register::parse (int argc, ACE_TCHAR **argv)
{
  // Check for enough arguments (we need at least one for the server name)
  if (argc < 2)
    {
      ORBSVCS_ERROR((LM_ERROR, "Error: Must supply at least a server name.\n"));
      this->print_usage ();
      return -1;
    }

  // Skip both the program name and the "update" command
  ACE_Get_Opt get_opts (argc, argv, ACE_TEXT("hqc:w:a:e:r:R:l:"));

  this->server_name_ = ACE_TEXT_ALWAYS_CHAR(argv[1]);
  int c;

  while ((c = get_opts ()) != -1)
    {
      switch (c)
      {
      case 'c':  // Command line arguments
        this->set_command_line_ = true;
        this->command_line_ = ACE_TEXT_ALWAYS_CHAR(get_opts.opt_arg ());
        break;
      case 'e':  // set environment variables
        this->set_environment_vars_ = true;
        this->addenv( get_opts.opt_arg () );
        break;
      case 'w':  // Working Directory
        this->set_working_dir_ = true;
        this->working_dir_ = ACE_TEXT_ALWAYS_CHAR(get_opts.opt_arg ());
        break;
      case 'a':  // Activation Mode
        this->set_activation_ = true;
        if (ACE_OS::strcasecmp (get_opts.opt_arg (), ACE_TEXT("NORMAL")) == 0)
          this->activation_ = ImplementationRepository::NORMAL;
        else if (ACE_OS::strcasecmp (get_opts.opt_arg (), ACE_TEXT("MANUAL")) == 0)
          this->activation_ = ImplementationRepository::MANUAL;
        else if (ACE_OS::strcasecmp (get_opts.opt_arg (), ACE_TEXT("PER_CLIENT")) == 0)
          this->activation_ = ImplementationRepository::PER_CLIENT;
        else if (ACE_OS::strcasecmp (get_opts.opt_arg (), ACE_TEXT("AUTO_START")) == 0)
          this->activation_ = ImplementationRepository::AUTO_START;
        else
          ORBSVCS_ERROR_RETURN ((LM_ERROR,
          "Unknown Activation Mode <%s>.\n",
          get_opts.opt_arg ()),
          -1);
        break;
      case 'r':
      case 'R':   // startup/ping Retry Count
        {
          this->set_retry_count_ = true;
          int rc = ACE_OS::atoi(get_opts.optarg);
          if (rc > 0)
            this->retry_count_ = rc;
        }
        break;
      case 'l': /// hostname of the activator
        this->activator_ = ACE_TEXT_ALWAYS_CHAR(get_opts.optarg);
        this->set_activator_ = true;
        break;
      case 'q' :
        this->quiet_ = true;
        break;
      case 'h':  // display help
        this->print_usage ();
        return -1;
      default:
        ORBSVCS_ERROR((LM_ERROR, "ERROR : Unknown option '%c'\n", (char) c));
        this->print_usage ();
        return -1;
      }
    }
  return 0;
}


// ============================================================================
// = Run methods


int
TAO_IMR_Op_Activate::run ()
{
  ACE_ASSERT(! CORBA::is_nil(imr_));
  try
    {
      this->imr_->activate_server (this->server_name_.c_str ());
      if (!this->quiet_)
        {
          ORBSVCS_DEBUG ((LM_DEBUG,
                          "Successfully Activated server <%C>\n",
                          this->server_name_.c_str ()));
        }
    }
  catch (const ImplementationRepository::CannotActivate& ex)
    {
      if (!this->quiet_)
        {
          ORBSVCS_ERROR ((LM_ERROR,
                          "Cannot activate server <%C> reason <%C>\n",
                          this->server_name_.c_str (),
                          ex.reason.in ()));
        }
      return TAO_IMR_Op::CANNOT_ACTIVATE;
    }
  catch (const ImplementationRepository::NotFound&)
    {
      if (!this->quiet_)
        {
          ORBSVCS_ERROR ((LM_ERROR,
                          "Could not find server <%C>.\n",
                          this->server_name_.c_str ()));
        }
      return TAO_IMR_Op::NOT_FOUND;
    }
  catch (const PortableServer::ForwardRequest&)
    {
      throw;
    }
  catch (const CORBA::Exception& ex)
    {
      if (!this->quiet_)
        {
          ex._tao_print_exception ("Activating Server");
        }
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}

int
TAO_IMR_Op_Autostart::run ()
{
  ACE_ASSERT(! CORBA::is_nil (imr_));

  ImplementationRepository::ServerInformationList_var server_list;
  ImplementationRepository::ServerInformationIterator_var server_iter;

  try
    {
      this->imr_->list (0,
        false,
        server_list,
        server_iter);

      ACE_ASSERT(CORBA::is_nil (server_iter.in ()));

      CORBA::ULong len = server_list->length ();
      for (CORBA::ULong i = 0; i < len; ++i)
        {
          try
            {
              this->imr_->activate_server (server_list[i].server.in ());
            }
          catch (const CORBA::Exception& ex)
            {
              ex._tao_print_exception (server_list[i].server.in ());
              // Ignore exception
            }
        }
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("autostart");
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}

int
TAO_IMR_Op_IOR::run ()
{
  ACE_ASSERT (! CORBA::is_nil(imr_));

  // Create a corbaloc string
  // Todo : Most of this logic duplicates that in the POA.cpp
  try
    {
      if (CORBA::is_nil (this->imr_)
        || !this->imr_->_stubobj ()
        || !this->imr_->_stubobj ()->profile_in_use ())
      {
        ORBSVCS_ERROR_RETURN ((
          LM_ERROR,
          ACE_TEXT ("Invalid ImR IOR.\n")
          ), -1);
      }

      CORBA::String_var imr_str =
        this->imr_->_stubobj ()->
        profile_in_use ()->to_string ();

      // Search for "corbaloc:" alone, without the protocol.  This code
      // should be protocol neutral.
      const char corbaloc[] = "corbaloc:";
      char *pos = ACE_OS::strstr (imr_str.inout (), corbaloc);

      if (pos == 0)
      {
        ORBSVCS_ERROR_RETURN ((LM_ERROR, "Could not parse IMR IOR.\n"), -1);
      }
      else
      {
        pos = ACE_OS::strchr (pos + sizeof (corbaloc), ':');
        pos = ACE_OS::strchr (pos + 1,
          this->imr_->_stubobj ()->profile_in_use ()->object_key_delimiter ());

        if (pos)
        {
          *(pos + 1) = 0;  // Crop the string
        }
        else
        {
          ORBSVCS_ERROR_RETURN ((LM_ERROR, "Could not parse IMR IOR.\n"), -1);
        }
      }
      ACE_CString ior (imr_str.in ());

      // Add the key
      const char jacorb[] = "JACORB:";
      const char *posjacorb = ACE_OS::strstr (server_name_.c_str (), jacorb);
      if (posjacorb)
      {
        ior += posjacorb + sizeof(jacorb) - 1;
      }
      else
      {
        ior += this->server_name_;
      }

      ORBSVCS_DEBUG ((LM_DEBUG, ACE_TEXT ("%C\n"), ior.c_str ()));

      if (this->filename_.length () > 0)
      {
        FILE *file = ACE_OS::fopen (this->filename_.c_str (), "w");

        if (file == 0)
        {
          ORBSVCS_ERROR_RETURN ((LM_ERROR,
            ACE_TEXT ("Error: Unable to open %s for writing: %p\n"),
            this->filename_.c_str ()),
            -1);
        }

        ACE_OS::fprintf (file, "%s", ior.c_str ());
        ACE_OS::fclose (file);
      }
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("IOR");
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}

int
TAO_IMR_Op_Kill::run ()
{
  ACE_ASSERT (! CORBA::is_nil(imr_));

  ImplementationRepository::AdministrationExt_var imrext =
    ImplementationRepository::AdministrationExt::_narrow (imr_);
  if (CORBA::is_nil (imrext.in()))
    {
      ORBSVCS_ERROR_RETURN
        ((LM_ERROR,
          ACE_TEXT ("Error: requested IMR does not support the kill operation\n")),
         -1);
    }

  try
    {
      imrext->kill_server (this->server_name_.c_str(), static_cast<CORBA::Short> (this->signum_));
    }
  catch (const ImplementationRepository::NotFound &)
    {
      if (!this->quiet_)
        {
          ORBSVCS_ERROR ((LM_ERROR,
                          "Could not find server <%C>.\n",
                          this->server_name_.c_str ()));
        }
      return TAO_IMR_Op::NOT_FOUND;
    }
  catch (const ImplementationRepository::CannotComplete& ex)
    {
      if (!this->quiet_)
        {
          ORBSVCS_ERROR ((LM_ERROR,
                          "Cannot complete kill of <%C> reason <%C>\n",
                          this->server_name_.c_str (),
                          ex.reason.in ()));
        }
      return TAO_IMR_Op::CANNOT_COMPLETE;
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Kill");
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}

int
TAO_IMR_Op_Link::run ()
{
  ACE_ASSERT (! CORBA::is_nil(imr_));

  ImplementationRepository::AdministrationExt_var imrext =
    ImplementationRepository::AdministrationExt::_narrow (imr_);
  if (CORBA::is_nil (imrext.in()))
    {
      ORBSVCS_ERROR_RETURN
        ((LM_ERROR,
          ACE_TEXT ("Error: requested IMR does not support the kill operation\n")),
         -1);
    }

  try
    {
      imrext->link_servers (this->server_name_.c_str(), this->peers_);
    }
  catch (const ImplementationRepository::NotFound &)
    {
      ORBSVCS_ERROR ((LM_ERROR,
                      "Could not find server <%C>.\n",
                      this->server_name_.c_str ()));
      return TAO_IMR_Op::NOT_FOUND;
    }
  catch (const ImplementationRepository::CannotComplete& ex)
    {
      ORBSVCS_ERROR ((LM_ERROR,
                      "Cannot complete kill of <%C> reason <%C>\n",
                      this->server_name_.c_str (),
                      ex.reason.in ()));
      return TAO_IMR_Op::CANNOT_COMPLETE;
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Kill");
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}


int
TAO_IMR_Op_List::run ()
{
  ACE_ASSERT (! CORBA::is_nil(imr_));

  ImplementationRepository::ServerInformationList_var server_list;
  ImplementationRepository::ServerInformationIterator_var server_iter;

  try
    {
      // If there is a server name, list only that server.  Otherwise, look
      // at all of them.
      if (this->server_name_.length () == 0)
        {
          this->imr_->list (this->how_many_,
            this->list_only_active_servers_,
            server_list.out(),
            server_iter.out());

          if (server_list->length() == 0)
          {
            ORBSVCS_DEBUG((LM_DEBUG, "No servers found.\n"));
            return TAO_IMR_Op::NORMAL;
          }

          for (CORBA::ULong i = 0; i < server_list->length (); i++)
            this->display_server_information (server_list[i]);

          if (!CORBA::is_nil (server_iter.in ()))
            {
              ORBSVCS_DEBUG ((LM_DEBUG, "An iterator was returned.\n"));
              for (bool done = false; !done; )
                {
                  done = server_iter->next_n (this->how_many_, server_list.out());
                  for (CORBA::ULong i = 0; i < server_list->length (); i++)
                    this->display_server_information (server_list[i]);
                }
              server_iter->destroy ();
            }
        }
      else
        {
          ImplementationRepository::ServerInformation_var si;

          this->imr_->find (this->server_name_.c_str (), si);
          if (ACE_OS::strlen (si->server.in()) > 0)
            {
              this->verbose_server_information_ = 1;
              this->display_server_information (si.in ());
            }
          else
            {
              throw ImplementationRepository::NotFound ();
            }
        }
    }
  catch (const ImplementationRepository::NotFound&)
    {
      ORBSVCS_ERROR ((LM_ERROR,
                      "Could not find server <%C>.\n",
                      this->server_name_.c_str ()));
      return TAO_IMR_Op::NOT_FOUND;
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("List");
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}

int
TAO_IMR_Op_Remove::run ()
{
  ACE_ASSERT (! CORBA::is_nil(imr_));

  try
    {
      if (this->force_)
        {
          ImplementationRepository::AdministrationExt_var ext =
            ImplementationRepository::AdministrationExt::_narrow (imr_);
          ACE_ASSERT (! CORBA::is_nil(ext));
          ext->force_remove_server (this->server_name_.c_str (),
                                    static_cast<CORBA::Short> (this->signum_));
        }
      else
        {
          this->imr_->remove_server (this->server_name_.c_str ());
        }
      ORBSVCS_DEBUG ((LM_DEBUG, "Successfully removed server <%C>\n",
        this->server_name_.c_str ()));
    }
  catch (const ImplementationRepository::NotFound&)
    {
      ORBSVCS_ERROR ((LM_ERROR, "Could not find server <%C>.\n",
        this->server_name_.c_str ()));
      return TAO_IMR_Op::NOT_FOUND;
    }
  catch (const ImplementationRepository::CannotComplete& cc)
    {
      ORBSVCS_ERROR ((LM_ERROR, "Could not complete forced removal of server <%C>. reason: %C\n",
                      this->server_name_.c_str (), cc.reason.in() ));
      return TAO_IMR_Op::CANNOT_COMPLETE;
    }
  catch (const CORBA::NO_PERMISSION& np)
    {
      if ((np.minor () & 0x7FU) == 0xFU) //TAO_EBUSY_MINOR_CODE)
        {
          ORBSVCS_ERROR ((LM_ERROR, "Server <%C> still busy.\n",
                          this->server_name_.c_str ()));
          return TAO_IMR_Op::CANNOT_COMPLETE;
        }
      ORBSVCS_ERROR ((LM_ERROR, "No Permission: ImplRepo is in Locked mode\n"));
      return TAO_IMR_Op::NO_PERMISSION;
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Removing Server");
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}

int
TAO_IMR_Op_Shutdown::run ()
{
  ACE_ASSERT (! CORBA::is_nil(imr_));

  try
    {
      this->imr_->shutdown_server (this->server_name_.c_str ());

      if (!this->quiet_)
        {
          ORBSVCS_DEBUG ((LM_DEBUG,
                          "Successfully shut down server <%C>\n",
                          this->server_name_.c_str ()));
        }
    }
  catch (const ImplementationRepository::NotFound&)
    {
      if (!this->quiet_)
        {
          ORBSVCS_ERROR ((LM_ERROR,
                          "Server <%C> already shut down.\n",
                          this->server_name_.c_str ()));
        }
      return TAO_IMR_Op::NOT_FOUND;
    }
  catch (const CORBA::TIMEOUT&)
    {
      if (!this->quiet_)
        {
          ORBSVCS_DEBUG ((LM_DEBUG,
                          "Timeout waiting for <%C> to shutdown.\n",
                          this->server_name_.c_str ()));
        }
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Shutting Down Server");
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}

int
TAO_IMR_Op_ShutdownRepo::run ()
{
  ACE_ASSERT(! CORBA::is_nil(imr_));

  try
    {
      bool servers = false; // not implemented yet, if ever
      this->imr_->shutdown (activators_, servers);

      ORBSVCS_DEBUG ((LM_DEBUG, "ImR shutdown initiated.\n"));
    }
  catch (const CORBA::TIMEOUT&)
    {
      ORBSVCS_DEBUG ((LM_DEBUG, "Timeout waiting for ImR shutdown.\n"));
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Shutting Down ImR");
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}

int
TAO_IMR_Op_Register::run ()
{
  ACE_ASSERT (! CORBA::is_nil(imr_));

  ImplementationRepository::ServerInformation_var server_information;
  ImplementationRepository::StartupOptions  local;
  ImplementationRepository::StartupOptions* options = 0;

  try
    {
      this->imr_->find (this->server_name_.c_str (),
        server_information.out ());

      if (server_name_ == server_information->server.in())
        {
          if (is_add_)
            {
              if (!this->quiet_)
                {
                  ORBSVCS_DEBUG((LM_DEBUG,
                                 "(%P|%t) ImR: Server <%C> already registered.\n",
                                 this->server_name_.c_str ()));
                }
              return ALREADY_REGISTERED;
            }
          options = &server_information->startup;
        }
      else // not found
        {
          if (!is_add_)
          {
            if (!this->quiet_)
              {
                ORBSVCS_DEBUG((LM_DEBUG,
                               "(%P|%t) Adding Server <%C> on update command.\n",
                               this->server_name_.c_str ()));
              }
            is_add_ = true;
          }
          local.activation= ImplementationRepository::NORMAL;
          options = &local;
        }

      if (this->set_command_line_)
        options->command_line = CORBA::string_dup (this->command_line_.c_str ());

      if (this->set_environment_vars_)
        options->environment = this->environment_vars_;

      if (this->set_working_dir_)
        options->working_directory = CORBA::string_dup (this->working_dir_.c_str ());

      if (this->set_activation_ || is_add_)
        options->activation = this->activation_;

      if (this->set_retry_count_ || is_add_)
        options->start_limit = this->retry_count_ + 1;

      if (this->set_activator_)
        options->activator = CORBA::string_dup(this->activator_.c_str ());
      // If the command line is set, we must have an activator
      else if (this->set_command_line_ &&
              (options->activator.in () == 0 || *options->activator.in () == 0))
        {
          char host_name[MAXHOSTNAMELEN + 1];
          ACE_OS::hostname (host_name, MAXHOSTNAMELEN);
          options->activator = CORBA::string_dup (host_name);
          if (!this->quiet_)
            {
              ORBSVCS_DEBUG ((LM_DEBUG,
                              "(%P|%t) ImR: Updating Server <%C> with default "
                              "activator of <%C>\n",
                              this->server_name_.c_str (),
                              options->activator.in ()));
            }
        }
      this->imr_->add_or_update_server (this->server_name_.c_str (), *options);

      if (!this->quiet_)
        {
          ORBSVCS_DEBUG((LM_DEBUG,
                         "(%P|%t) ImR: Successfully registered <%C>\n",
                         this->server_name_.c_str ()));
        }
    }
  catch (const CORBA::NO_PERMISSION&)
    {
      ORBSVCS_ERROR ((LM_ERROR, "(%P|%t) ImR: No Permission: ImplRepo is in Locked mode\n"));
      return TAO_IMR_Op::NO_PERMISSION;
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Updating server");
      return TAO_IMR_Op::UNKNOWN;
    }

  return TAO_IMR_Op::NORMAL;
}

// ============================================================================
// = Display Server Information methods

void
TAO_IMR_Op_List::display_server_information (const ImplementationRepository::ServerInformation &info)
{
  const char *maybe = "";
  if (this->list_only_active_servers_)
    {
      switch (info.activeStatus)
        {
        case ImplementationRepository::ACTIVE_NO:
          return;
        case ImplementationRepository::ACTIVE_MAYBE:
          maybe = "(maybe)";
          break;
        default:
          break;
        }
    }

  if (this->verbose_server_information_)
    TAO_IMR_Op::display_server_information (info);
  else
    {
      if (this->terse_)
        ORBSVCS_DEBUG ((LM_DEBUG, "%C\n", info.server.in ()));
      else
        ORBSVCS_DEBUG ((LM_DEBUG, "<%C> %C\n", info.server.in (), maybe));
    }
}
