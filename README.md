## Decryptor For Paymen45 Ransomware (.g8R4rqWIp9)


### Two Features Support 

#### Automatic Decryption Key Extraction From Ransomware Process Memory And Decrypt File Using it

```cmd
.\CLI.exe RansomwareProcessID DirectoryToDecrypt
```
> Example: .\CLI.exe 1690 C:\

#### Provide Decryption Key Manually And Decrypt File

```cmd
.\CLI.exe -k DecryptionKey DirectoryToDecrypt
```

> Example: .\CLI.exe -k AA06E65714F2482BBA05B2336956552829AB7268B41F83186AB9E278A0926D84 C:\  


# Warning!!!!!

This decryptor use a logic flaw in paymen45 to extract the key. Also the Decryption key changes everytime the ransomware run.
if you have been already infected and if the ransomware process is not running for the first time don't use this. Also if you apply a wrong key your file will be never recoverable.


## FAQ 

### In which condition can i use this tool?
> As soon as you know your computer got attacked by paymen45 ransomware for the first time and the ransomware process is still running.

