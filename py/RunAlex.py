import os
import os
import errno


Detector="MagBox"
Gas="Xe"
Signal="Xe136_bb0nu"


mode="ALEX"
levelDebug="DEBUG"

startEvent=0 
finalEvent=10
eventsDebug=10
pressure=10 #atm
bfield=0 #tesla 
energyFWHM=0.005 
xySigma=1 #mm
zSigma=1 #mm 


if __name__ == "__main__":


	alex_dst_dir=os.environ["ALEX_DST"]
	alex_histos_dir=os.environ["ALEX_HISTOS"]
	irene_dst_dir=os.environ["IRENE_DST"]	
	irene_histos_dir=os.environ["IRENE_HISTOS"]

	BF={0.:"00tesla",0.1:"01tesla",0.2:"02tesla"}
	PR={10:"10atm",5:"5atm",15:"15atm"}

	magfield=BF[bfield]
	Pressure=PR[pressure]
	

	run_name=Detector+"_"+Gas+"_"+Pressure+"_"+magfield+"."+Signal 
	print "run_name =",run_name

	alex_dst=run_name+".alex.root"
	print "alex_dst =",alex_dst

	alex_histo=run_name+".histos.alex.root"
	print "alex_histo =",alex_histo

	alex_dst_path=alex_dst_dir+"/"+alex_dst
	print "alex_dst_path =",alex_dst_path

	alex_histo_path=alex_histos_dir+"/"+alex_histo
	print "alex_histo_path =",alex_histo_path

	dst=""
	histo=""

	if mode == "ALEX":
		dst=alex_dst_path
		histo=alex_histo_path

	
	
	command1="bin/xAlex --levelDebug %s --mode %s --dst %s --histo %s "%(levelDebug,mode,dst,histo)
	command2=" --startEvent %d --finalEvent %d --eventsDebug %d "%(startEvent,finalEvent,eventsDebug)
	command3=" --pressure %d --bfield %d --energyFWHM %f"%(pressure,bfield,energyFWHM)
	command4=" --xySigma %d --zSigma %d"%(xySigma,zSigma)

	command=command1+command2+command3+command4
	print command
	os.system(command)

	
	

