
export ALEX_BUILD_LIB=$ALEX_BUILD/lib
export ALEX_BUILD_BIN=$ALEX_BUILD/bin

export PATH=$ALEX_BUILD_BIN:$ROOTSYS/bin:$INSTALL/bin:$PATH
export DYLD_LIBRARY_PATH=$ALEX_BUILD_LIB:$ROOTSYS/lib/:$INSTALL/lib:$DYLD_LIBRARY_PATH
export LD_LIBRARY_PATH=$DYLD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH:$ALEX/py
alias setupalex="python /Users/jjgomezcadenas/Development/devnext/alex/py/SetupBuildAlex.py"
