import os
import os
import errno







if __name__ == "__main__":

	alex_xml_dir=os.environ["ALGO_CONF"]
	alex_src_dir=os.environ["ALGO_SRC"]
	
	
	levelDebug="DEBUG"

	algoConfigPath=alex_xml_dir+"/AlgoConfig.xml" 
 	srcDirPath= alex_src_dir
 
	
	command="bin/xConfigure --levelDebug %s --algoConfigPath %s --srcDirPath %s "%(levelDebug,
		algoConfigPath,srcDirPath)
	
	print command
	os.system(command)

	
	

