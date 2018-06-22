# predict_iv

# build
run build.bat for windows or build.sh<br/>
change directory to build and launch(win) or run make and make install( linux)<br/><br/>
installation file will be located in ./install folder

# command line
provide path to the test file as the first command line argument<br/>
./predict <path> <br/>

# idea
utilize prior knowledge on data distribution and in the same time keep the predictor app simple.<br/>
First, I'm trying to analyze the data and get baseline scores for popular classifiers. Then the solution is build based on the analysis.

# submissions
submission.csv - classifier based on engeneered features<br/>
submission_joint.csv - classifier based on both original and engeneered features<br/>