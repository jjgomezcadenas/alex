import os
import sys
import errno

def cond_mkdir(path):
    try:
        os.makedirs(path)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise

if __name__ == "__main__":

	if len(sys.argv) !=3:
		print "usage: python ConfigureAlexRun.py <AlexConfigFile> <AlgoConfigFile>"
		sys.exit(-1)

	alex_dir=os.environ["ALEX"]
	xml_dir=alex_dir+"/algos/xml"
	alexConfig = sys.argv[1]
	algoConfig = sys.argv[2]

	print "xml dir = ", xml_dir
	print "alexConfig file = ", alexConfig
	print "algoConfig file = ", algoConfig

	pathAlexConfig =xml_dir+"/"+alexConfig
	
	if os.path.exists(pathAlexConfig):
		print "found: ", pathAlexConfig
	else:
		print "not found: ",pathAlexConfig
		sys.exit(-1);

	pathAlgoConfig =xml_dir+"/"+algoConfig
	
	if os.path.exists(pathAlgoConfig):
		print "found: ", pathAlgoConfig
	else:
		print "not found: ",pathAlgoConfig
		sys.exit(-1);

	command="ln -sf "+pathAlexConfig+" "+xml_dir+"/AlexConfig.xml"
	print "excuting: ->", command
	os.system(command)
	command="ln -sf "+pathAlgoConfig+" "+xml_dir+"/AlgoConfig.xml"
	print "excuting: ->", command
	os.system(command)
