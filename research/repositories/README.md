# Research repositories (externally maintained)

The entries in this directory are kept in `idowatch` as gitlink placeholders, not checked out by default after cloning this repo.  
They are useful for protocol browsing and reverse engineering, but the source lives in their own upstream Git remotes.

After cloning `idowatch`, fetch the exact versions you need with:

```bash
mkdir -p research/repositories
cd research/repositories

git clone https://github.com/idoosmart/Flutter_GitBook.git Flutter_GitBook
git clone https://github.com/idoosmart/IDOAndroidBleSDK-_UPDATE.git IDOAndroidBleSDK_UPDATE
git clone https://github.com/idoosmart/IDOBlueProtocol.git IDOBlueProtocol
git clone https://github.com/idoosmart/IDOGitBook.git IDOGitBook
git clone https://github.com/Coolsteel217/IWFmake.git IWFmake
git clone https://github.com/orangebrush/angelfit.git angelfit
git clone https://github.com/idoosmart/IDOAndroidBleSDK.git IDOAndroidBleSDK

cd Flutter_GitBook && git checkout e18a84718de2b9e7c8e353fcfee49d26f6494d4a
cd ../IDOAndroidBleSDK_UPDATE && git checkout 070cd9e205cadd65e898a71729b6230d63fa7902
cd ../IDOBlueProtocol && git checkout 33ae35b8e3076b83c924a5864247bb29432dd9aa
cd ../IDOGitBook && git checkout 8ee726f251d5b15be0389126f35276e722248f96
cd ../IWFmake && git checkout b2b39e93e68d29bb798bd0386678ae4ab6fc30b4
cd ../angelfit && git checkout 94969fb207c1d15b6a4f70b078fd8608c79478a3
cd ../IDOAndroidBleSDK && git checkout cd1a4c668860b668bb17a0e2c1a79a97c6bc2247
```

`gadgetbridge/` is handled separately below and is kept as a dedicated sub-repository in
[`/gadgetbridge`](../..), with code tracked directly in its own repo at
`https://github.com/d3nd3/gadgetbridge-veryfit`.
