## Definition

__Genesis block__ is first block in the blockchain, it's special in a way that it doesn't have predecessor.
__Genesis transaction__ is a transaction that appears in genesis block. It is included because block must have at least one transaction. It is special in a way that it doesn't spend any outputs(because there is simply no unspent outputs at this time) which normally is not allowed.

### Creating genesis block

In order to create new genesis block you need to change few parameters:
```
1. Genesis block time
2. Genesis transaction (optional)
3. Genesis block nonce
```

Changing any of those parameters changes block hash which breaks assertions placed in code, they need to be fixed as well. 
Everything related to genesis block lives in chainparams.cpp. 

### Changing block time

This piece of code from chainparams.cpp fills genesis block with predefined parameters: 

```
genesis.hashMerkleRoot = genesis.BuildMerkleTree();
genesis.nVersion = 1;
genesis.nTime = 1545134400;
genesis.nBits = 0x1e0ffff0;
genesis.nNonce = 868485;
genesis.payee = txNew.vout[0].scriptPubKey;

```

In order to change time grab current epoch timestamp in seconds and place it in `genesis.nTime`. 

### Changing genesis transaction (Optional)

This piece of code from chainparams.cpp creates genesis transaction with predefined parameters:

```
const char* pszTimestamp = "DMTC was created for gaming platform dominant chain";
CMutableTransaction txNew;
txNew.vin.resize(1);
txNew.vout.resize(1);
txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
txNew.vout[0].nValue = 50 * COIN;
txNew.vout[0].scriptPubKey = CScript() << ParseHex("043360a496ec47307cc8ebc3d59b413626eb8b0cde57d1d9bbc6beda174474c9506fb666c9da4a4d9694bf4e6e422fa0347bb4f73192de3246c02d144db1e47c69") << OP_CHECKSIG;
genesis.vtx.push_back(txNew);

```

User may want to change `pszTimestamp` or `scriptPubKey` for genesis transaction. Changing amount doesn't affect anything because this transaction is unspendable. 

### Mining genesis block

Changing any of parameters that were described before will change block hash breaking assertions. Running client at this point will end up with crash on line: `assert(hashGenesisBlock == uint256("0x00000e258596876664989374c7ee36445cf5f4f80889af415cc32478214394ea"));`. To fix that we need to find nonce and hash for new genesis block. We will use `MineGenesis` function for that. 

We need to set `nNonce = 0;` and call `MineGenesis(genesis)` before these lines:

```
hashGenesisBlock = genesis.GetHash();
assert(hashGenesisBlock == uint256("0x00000e258596876664989374c7ee36445cf5f4f80889af415cc32478214394ea"));
assert(genesis.hashMerkleRoot == uint256("0xec803cc6b5e68728ec0117cb1154b6d2893152f89d61319647db106908888bd6"));
```

Calling `MineGenesis` will output new values for genesis block, grab block hash, merkle tree hash and nNonce and replace corresponding values. Remove call to `MineGenesis`. At this point everything has to work.

Don't forget to remove dmtc home folder to remove old blocks. 

This process can be done for any network, mainnet, testnet or regtest. 