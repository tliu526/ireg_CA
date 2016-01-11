#Implementation Journal
__More recent entries are at the top.__

##1/11/2016
Morning: Implemented Regular Grid Generator, some basic stencils.

###Results of Local Majority Baseline Experiment (Regular, Non-Periodic)

![](LM_Baseline_Reg.jpg)

![](LM_Baseline_Reg_Large.jpg)

These results show a more rapid degradation in performance than in me07, though this may be due to the non-periodic boundaries.

##1/8/2016
Morning Goal: Set up replication of Messinger et al.'s (me07) baseline local majority computation. 

Relevant Parameters:
- 15 by 15 grid (225 cells)
- Increments of 1 percent from 1:99 on/off ratio to 99:1
- Maximum of 450 time steps
- Only concerned with completely correct classification
- 1000 randomly assigned initial network configurations for each initial ratio

Afternoon: Finished replication of LM baseline computation. In order to account for variations in irregular grids, ran 10 different grid configurations with 100 random initial starting configruations for each initial ratio, for 1000 total.

1,000 simulations takes ~2.5 minutes, 10,000 simulations takes ~20-25 minutes.

###Goals for Tuesday
- Look at Wooters (wo90), Hill (hi05), Messinger (me07) for any other experiments that can be easily performed
- Replicate LM Baseline with a standard regular grid to verify correct performance
- Have some basic visualization of the interesting values for LMBaseline
- Keep scripting and modularity in mind, look into rigging up call-back functions

###Results of Local Majority Baseline Experiment (Irregular)

![](LM_Baseline.jpg)

![](LM_Baseline_Large.jpg)

These graphs resemble the same data presented in Messinger for regular grids, with symmetric degradation of performance for both ON and OFF majority. However, there is a slightly slower degradation of performance in the irregular case than the regular case, with approximately 60% task performance for irregular configurations at 20:80 and 80:20 and approximately 40% task performance for regular configurations at 20:80 and 80:20 (me07). We will exactly replicate the original Messinger experiments as a comparison.

##1/7/2016
Morning: Finished SimpleMajorityRule as well as RuleTable and Stencil. Rudimentary majority task simulations can now be run.

Afternoon: Laid out foundation for updating and writing metrics within the Simulator event loop. 

Evening: Implemented a simple checksum using STD hash to store previous grid state. TODO implement md5 hash for the checksum, STD hash collision rate remains to be tested.

##1/6/2016
This morning: implemented variatic Properties to be stored in cells using unions. GridGenerators can now write different property lists to file.

This afternoon: laid out foundation for Stencil class, which maps a rule table to an irregular neighborhood. SimpleMajorityRule almost complete.

##1/5/2016

###__Week 1 Goals__
- Get a working simulation up and running, with rule applications and simple statistics tracking
- Concept of a Rule Table ("traditional" rule numbering/declarations) and Rule Mapping (to irregular grids)

Today, laid out the foundation of the Simulation class, and it now performs a dummy
simulation. Next steps are to continue to flesh out the Simulation so that actual
computation is being performed.

Things to keep in mind:
- Scriptability
- Modularity