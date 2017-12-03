# NLNRI_VCVRackPlugins
Nonlinear instruments as VCV Rack plugins

## QU4Dit module
<img src="https://github.com/NonLinearInstruments/NLNRI_VCVRackPlugins/blob/master/res/QU4DiT_shot.jpg" align="left" />
The Quadratic iterator, also known as Logistic map (after the Verhulst's logistic equation) is a simple one-dimensional model with chaotic behavior. It has a single parameter (here named "C").<br/>
This module explores the region for parameter values above roughly 3.5, where chaos happens.<br/>
cv input expects unipolar signal ( 0 ~ 10 ).<br/>
There are two quadratic iterators running, one for the X output, the other for the Y output.<br/>
Offset allows to desplace C parameter for the Y iterator.<br/>
