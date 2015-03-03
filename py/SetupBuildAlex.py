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

	build_dir=os.environ["ALEX_BUILD"]
	lib_dir=os.environ["ALEX_BUILD_LIB"]
	bin_dir=os.environ["ALEX_BUILD_BIN"]
	cond_mkdir(lib_dir)
	cond_mkdir(bin_dir)

	base_dir=build_dir+"/base"
	command="ln -sf "+base_dir+"/libabase*.* "+lib_dir+"/."
	os.system(command)

	admodel_dir=build_dir+"/admodel"
	command="ln -sf "+admodel_dir+"/libadmodel*.* "+lib_dir+"/."
	os.system(command)

	svc_dir=build_dir+"/svc"
	command="ln -sf "+svc_dir+"/libasvc*.* "+lib_dir+"/."
	os.system(command)

	algos_dir=build_dir+"/algos/src"
	command="ln -sf "+algos_dir+"/libaalgos*.* "+lib_dir+"/."
	os.system(command)

	config_dir=build_dir+"/config"
	command="ln -sf "+config_dir+"/libaconf*.* "+lib_dir+"/."
	os.system(command)

	main_dir=build_dir+"/main"
	command="ln -sf "+config_dir+"/xConfigure "+bin_dir+"/."
	os.system(command)

	command="ln -sf "+main_dir+"/xAlex "+bin_dir+"/."
	os.system(command)

	

