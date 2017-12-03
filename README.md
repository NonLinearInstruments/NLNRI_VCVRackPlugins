# NLNRI_VCVRackPlugins
Nonlinear instruments as VCV Rack plugins

## QU4Dit module
<img src="https://github.com/NonLinearInstruments/NLNRI_VCVRackPlugins/blob/master/res/QU4DiT_shot.jpg" align="left" />
###
The Quadratic iterator, also known as Logistic map (after the Verhulst's logistic equation) is a simple one-dimensional model with chaotic behavior. It has a single parameter (here named "C").
This module explores the region for parameter values above roughly 3.5, where chaos happens.
cv input expects unipolar signal ( 0 ~ 10 ).
There are two quadratic iterators running, one for the X output, the other for the Y output.
Offset allows to desplace C parameter for the Y iterator.
