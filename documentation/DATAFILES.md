# Data Directory

## Definition

__Data dir__ is a special folder that holds all information regarding the blockchain and p2p network.

## Location

Data dir is located in platform specific folder, currently 3 systems are supported:

- Windows: %AppData%/Roaming/DMTC
- Linux: ~/.dmtc
- OSX: ~/Library/Application\ Support/DMTC

Data dir location can be changed on startup using `-datadir=path/to/dir` startup argument

## Files description

- `backups`: folder for automatic wallet backups
- `blocks`: folder that contains database of blocks that were downloaded from p2p network. 
- `chainstate`: folder that contains database of blocks index which is needed to navigate blocks
- `debug.log`: debug prints from client. Usually is needed to solve some problem. 
- `dmtc.conf`: special file which holds startup configuration. Instead of using startup arguments when calling dmtcd, better approach is to put them into dmtc.conf, line by line. 
- `fee_estimates.dat`: cache of latest fees that were paid on the blockchain, needed for smart-fee estimation.
- `masternode.conf`: stores configuration for masternodes that are controlled by this wallet. This file needs to be filled if users is willing to run a masternode.
- `mncache.dat`: database that stores information about masternodes that are known to this node. Used to prevent spamming network with masternode requests on each run.
- `mnpayments.dat`: database that stores information about masternode payments. Used to verify & confirm that masternode payment is valid.
- `netfulfilled.dat`: local cache of completed network requests. 
- `peers.dat`: database that stores information about peers in p2p network. Used by client to quikly connect to well known peers.
- `sporks`: folder that contains database of sporks that were synced from p2p network. 
- `testnet3`: optional folder that contains same folder structure as mainnet folder but has data for testnet. 
- `wallet.dat`: the most important file. Stores private keys for your addresses. Losing this automatically means losing access to all of yours dmtc coins.