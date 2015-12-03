local_dir := mdp

local_src := action.cpp
local_src += learningStrategy.cpp
local_src += mdpModel.cpp
local_src += noLearning.cpp
local_src += policy.cpp
local_src += rewards.cpp
local_src += stateSpace.cpp
local_src += stateSpaceBuilder.cpp
local_src += stateSpaceDimension.cpp 
local_src += transitionMatrix.cpp



sources += $(addprefix $(local_dir)/,$(local_src))











