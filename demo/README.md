# REANA Tutorials

## About
These tutorials have been developed for the PHENIX School'21, however
materials presented here are general enough to be of a wider interest.
Each REANA workflow in this series of examples is described in a separate
YAML file so the description below is structured accordingly.

## Hello World 1

The file ```helloworld1.yaml``` contains a trivial example of a REANA workflow.
Things to note:
* The ```inputs``` section defines the inputs to the workflow. In this case,
the "file" type of attribute is used to describe a single file.
* The ```outputs``` section defines the outputs of the workflow, in this
case a single text file. Its purpose is to inform the REANA service
about what files need to be downloaded upon the workflow completion
when the user chooses to run the "download" command of the REANA client.

## Hello World 2
The file ```helloworld1.yaml``` contains an example of a REANA workflow
which is very similar to "Hello World 1", with the following differences:
* The ```inputs`` section contains a reference to a directory. In this case,
the client will upload the complete directory to the service.


