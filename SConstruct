import os

AddOption("--debug-build",
          action="store_true", dest="debug",
          help="Compile with debug information and warnings")
AddOption("--release",
          action="store_false", dest="debug", default=False,
          help="Compile without debug information and warnings [default]")

env = Environment( ENV = os.environ )

global_env = env

Export( 'global_env')

SConscript( 'src/SConscript' )
