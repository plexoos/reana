# REANA Tutorials

## About
These tutorials have been developed for the PHENIX School'21, however
materials presented here are general enough to be of a wider interest.
Each REANA workflow in this series of examples is described in a separate
YAML file so the description below is structured accordingly.

## The REANA client

For the purposes of this tutorial we assume that work is done
on interactive nodes of the SDCC computing farm, i.e. one of
the available "rcas" machines.

Activate the client package by using the command
```csh
source /direct/phenix+u/mxmp/.virtualenvs/reana/bin/activate.csh
```

## Hello World 1

The file ```helloworld1.yaml``` contains a trivial example of a REANA workflow.
Things to note:
* The ```inputs``` section defines the inputs to the workflow. In this case,
the "file" type of attribute is used to describe a single file.
* The ```outputs``` section defines the outputs of the workflow, in this
case a single text file. Its purpose is to inform the REANA service
about what files need to be downloaded upon the workflow completion
when and if the user chooses to run the "download" command of the REANA client.
* The ```environment``` in this case is the image of Ubuntu 18.04. This means that this
example workflow will run in the corresponding container. Since the workflow in this case
is a trivial shell operation, the exact flavor of Linux doesn't really matter.

## Hello World 2
The file ```helloworld2.yaml``` contains an example of a REANA workflow
which is very similar to "Hello World 1", with the following differences:
* The ```inputs``` section contains a reference to a directory. In this case,
the client will upload the complete directory to the service.
* The ```outputs``` section contains a reference to a directory. Similar to
the previous example, this provides a handle to the REANA client to download
the contents if requested by the user.

