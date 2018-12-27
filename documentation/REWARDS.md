# Rewards

## Definition
__Block subsidity__ is a value in Dmtc which is created (minted) every new block. Rewards are sent to different parties (Stakers, Masternodes). Will cover payments in next sections.
__Superblock__ is a special block which creates a payment to treasury or something else in perspective.

## Subsidy over the time

| Block height |  Subsidy  |
| ------------ | --------- |
|    1-300	   |  0.00001  |
| 301-11000	   |  0.00001  |
| 11000-62400  |    26,5   |
| 62400-122400 |    36,5   |
|122401-186400 |    50     |
|186401-250400 |    60     |
|250401-314400 |    20     |
|314401-378400 |    15     |


## Ordinary Block Rewards

In every block, there is one required payment. The Staker.
Stakers get rewarded based on current protocol setting; default value is 6%.

If there are masternodes that are ready to get paid, they get 88% of the block.

6% is reserved for payment to the treasury

All of those values can be changed by spork.

`CBlockRewards GetBlockSubsidity(int nHeight)` in `main.cpp` is the place where block rewards are calculated.

