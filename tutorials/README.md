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

Now you can check if the client application is now available to you:
```csh
reana-client --help
```
This will produce a very helpful screen with information about
various options and commands that can be used with the client.
It is a good idea to read it at least once, carefully.

If this worked, you can now proceed to check connectivity with the
REANA server. To do that, you need to set up two environment variables,
one with the secret token to authenticate yourself for the server,
and the other with the server URL so the client knows what to connect to.
```csh
# Set the variables:
setenv REANA_ACCESS_TOKEN _your_token_
setenv REANA_SERVER_URL https://kubmaster01.sdcc.bnl.gov:30443
# Ping the server
reana-client ping
```

## Running a workflow
In the example below the YAML file can be any file that contains
a workflow description of your choice. If the file is not specified
with the ```-f``` option, the client will attempt to find the default
file ```reana.yaml```. The ```-w``` option allows the user to assign
descriptive names to their workflows. If no such option is provided
the client will default to the name "workflow".
```csh
reana-client run -f my_workflow_file.yaml -w my_custom_workflow_name
```
If the same workflow is submitted under the same name multiple times
the server will assign serial numbers automatically. If you created
a workflow named "test" three times, the respective objects can be
access by the REANA client under the names __test.1, test.2, test.3__.
The following command will list all the worflows created by the user:
```csh
reana-client list
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

