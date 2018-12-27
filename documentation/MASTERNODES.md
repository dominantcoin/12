## Definitions

__Masternodes__ are computers that run a dmtc wallet and perform utility functions for network such as storing metadata and processing special transactions.

__Masternode collateral__ amount that is needed to run a masternode, each masternode wallet needs to lock a certain amount of DMTC in the wallet in order to register as a masternode in the network. 

__Masternode tier__ is the type of masternode, there are 3 types of masternodes (Bronze, Silver, Gold). Depending on the type, the owner will get more rewards and provide different services to the network.

## Masternode rewards

Every masternode forms a second layer of the network which enables the blockchain to perform additional functions. Masternodes are paid for performing these functions from block rewards. Default breakout is:


| Type | Reward (%) |
| -------- | ----------- |
| Staking | 6 |
| Masternode | 88 |
| Treasury | 6 |
| Proposals | 0 | 
| Charity | 0 | 

Payments layout can be changed by spork in any way.


## Payment logic

Masternode payments in Dmtc are determined using a decentralized random selection algorithm based on masternode level. Every masternode appears in the global list. Once a masternode is active for some amount of time, it is eligible for payments. Once eligible, it takes part in a probabilistic process that determines the winner for next block. Different levels have different chances to win.

## Winner selection

When a new block is added to the network, every masternode submits a vote for the winner, which appears in 10 blocks in future. Voting is a probabilistic process of selecting masternode winner. 

__Score__ is a double SHA256 of the funding transaction hash and ticket index for all masternodes in the selection pool. The score is compared with the block hash 100 blocks ago. The masternode with the closest numeric hash value to that block hash receives the payment. 


## Supporting the Dmtc Network

What is a masternode, really?   It's just a piece of software.  It's an app that's already built in to the Dmtc desktop wallet.  You launch the app, "fund" it with some of your DMTC coins, and it will go to work once it's connected with enough other nodes.  Those other nodes are owned by other DMTC masternode holders around the world, who have gone through the same process. 

What does a masternode actually do?  Dmtc's masternodes remain in constant contact with other nodes in the network.   Through this communication they verify and process transactions and keep everything secure, while continuously maintaining an up-to-date copy of the ledger.  Approximately every minute, one of the masternodes wins the right to add the latest block to the Dmtc blockchain.  That winner collects all the transactions, writes them into the block, and gets paid in DMTC.  Other masternodes verify everything, and if all is good, the blockchain grows.  

Masternode holders aren't getting DMTC for free.  They are paid for the work they're doing, which requires the following:

* *Continuously Staking Coins* - Masternode holders "stake" their coins, keeping them tied up while they run their masternode.  These coins remain in the user's wallet, but can't be spent or moved while the masternode is in operation.
* *Computer Equipment* - Some masternode holders choose to set up a dedicated computer just for their masternode, although this isn't necessary.  The computer that's used for this should be be left on 24/7 .  So like any piece of electronic equipment it maybe get some wear and tear, and require occasional maintenance.
* *Cloud Install* - You don't need a computer for this.  You can host a masternode in the cloud with our system.  There's a small monthly fee, which is deducted from your account, in DMTC, automatically each month.
* *Power Bills* - Unlike power-hungry Bitcoin mining, masternodes don't use much power or require custom equipment.
* *Internet* - You'll need a connection that's fast enough to handle the traffic required to keep your copy of the ledger updated and keep in contact with your peer nodes.
* *Software Updates* - Dmtc makes this easy with automatic updates
* Staying current on Dmtc news.  Participating in our ecosystem.  Voting in our governance.

What happens if the masternode goes down?  Perhaps power is lost or a computer needs to be repaired.  For whatever reason, it will disconnect from the network, and during this time no rewards can be earned.  Once re-connected, it will download the latest version of the Dmtc ledger and will start earning coins again.  

For the reasons of maintenance and stopping/starting, many people will opt to host their masternode in the cloud, which pays the same rewards and is even easier to do.