# Proc IntelliJ Plugin

Enables editing of .proc files.


Configure
---------

To use proxy for Gradle, create file `C:\Users\User\.gradle\gradle.properties` and add lines:
```
systemProp.http.proxyHost=host_ip_or_domain
systemProp.http.proxyPort=8080
systemProp.http.proxyUser=user
systemProp.http.proxyPassword=password
systemProp.http.nonProxyHosts=127.0.0.1,::1,localhost,192.168.*.*

systemProp.https.proxyHost=host_ip_or_domain
systemProp.https.proxyPort=8080
systemProp.https.proxyUser=user
systemProp.https.proxyPassword=password
systemProp.https.nonProxyHosts=127.0.0.1,::1,localhost,192.168.*.*
```

Fix `C:\Program Files\Microsoft\jdk-11.0.12.7-hotspot\Packages does not exist.` error by adding missing `Packages` folder.
