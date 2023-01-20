
jaClac
======

This folder contains a Java implementation of Clac. There are three components. The jClac
subfolder contains a standalone Java application for the desktop. The aClac subfolder contains
an Android version of Clac. The Common subfolder contains code that is shared between jClac and
aClac.

Roughly speaking the Common subfolder contains the Clac engine and supporting Clac entities, and
the jClac and aClac folders contain user interface code for their respective platforms.
Additional versions of Clac, for example an applet for a web browser, would hopefully be able to
use the same Common folder but have its own UI folder.

*NOTE* The Java version(s) of Clac are immature and not maintained. They were never more than
skeletons. They are being retained in the hope that they may be developed more in the future.

The jClac project uses IntelliJ IDE as its build environment (open the jClac folder). The aClac
project uses Android Studio as its build environment (open the aClac folder).

TODO
----

Android Studio uses Gradle as its build system and it can't (currently) import the Common module
since that module is not a Gradle-based build. Probably what needs to happen is the jClac
project needs to migrate to Gradle, including the Common module, and then the Common module may
be importable into aClac. Until then aClac is seriously broken.

Peter Chapin  
chapinp@proton.me  
