# CWeb
## A framework for making web apps in C
Yes really.
### Why
This is a learning project to learn about effective memory management, performance code, and software engineering in general.
We also want to prove that with good software development practices it's possible to write elegant code in C.


### The project

The project is in its very early stages. It's meant to be very lightweight, to run on machines with few resources. We hope to do so by removing layers between the the machine and the framework API, by focusing on the functionality required by web applications.

As of now it can bind to a port and handle requests, with routing and pass them through handler chains. It has a kernel that can be used to implement services that provide functionality in the handlers.

Planned features:
* a minimal strings library (in progress)
* configuration files parsing (in progress)
* forms and files handling
* SSH
* a templating language
* database abstraction

Possible features:
* a small compiled language with garbage collection
* an interactive console


#### Installation
Dependencies:
* C99 compatible compiler (a moderately recent version of gcc or clang definetly works)
* bash compatible shell
* uses git and CMAKE to install its dependencies in a local folder
* although unlikely, on some system the package onion may fail to compile due to some very small missing packages. The CMAKE output logs should help debug such issues.

`./run.sh` will install it's other dependencies in a subfolder, does not require root permissions.

#### Build
The console commands in `run.sh` will automatically rebuild and run the project or its tests.
