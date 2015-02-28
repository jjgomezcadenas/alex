import os
import os
import errno

def cond_mkdir(path):
    try:
        os.makedirs(path)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise

if __name__ == "__main__":

	build_dir = "/Users/jjgomezcadenas/Development/build/alex-build"
	lib_dir=build_dir+"/lib"
	bin_dir=build_dir+"/bin"

	cond_mkdir(lib_dir)
	cond_mkdir(bin_dir)

	base_dir=build_dir+"/base"
	command="ln -sf "+base_dir+"/libabase*.* "+lib_dir+"/."
	os.system(command)

	admodel_dir=build_dir+"/admodel"
	command="ln -sf "+admodel_dir+"/libadmodel*.* "+lib_dir+"/."
	os.system(command)

	config_dir=build_dir+"/config"
	command="ln -sf "+config_dir+"/libaconf*.* "+lib_dir+"/."
	os.system(command)

	svc_dir=build_dir+"/svc"
	command="ln -sf "+svc_dir+"/libasvc*.* "+lib_dir+"/."
	os.system(command)

	command="ln -sf "+svc_dir+"/xConfigure "+bin_dir+"/."
	os.system(command)

	os.environ["PATH"]=bin_dir+":$PATH"
	command ="export PATH="+bin_dir+":$PATH"
	os.system(command)
	
	command="export DYLD_LIBRARY_PATH="+lib_dir+":$DYLD_LIBRARY_PATH"
	os.system(command)
	command="export LD_LIBRARY_PATH=$DYLD_LIBRARY_PATH"
	os.system(command)

	os.environ["TEST"]="OK"
	os.system("echo $TEST")

