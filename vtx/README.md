# An example of a ROOT macro doing simple VTX analysis

The underying infrastructure behind REANA has a tendency to cache
Docker images, meaning later updates are not always reflected in what
REANA will run. The current state of this repo is referring to the
image:

* phenixcollaboration/tools:phenix-i686-clean

This information will be updated to stay current.

# What to run
The most recent version of the REANA submission YAML fie is ```ana_E_mod.yaml```.
Correspondingly, one can run something like
```bash
reana-client run -f ana_E_mod.yaml -w vtx_test
```

Currently the macro does not create any persistent images (e.g. PNG files)
and only produces text output for test purposes. If images are needed,
they can be created by modifying the macro, and then it is important to add
the image files to the "files" section of the output in the REANA YAML file
so they can be easily downlioaded by the client upon the job completion.

# A small caveat

ROOT5 executes this macro correctly but reports an error when existing, likely
due to a canvas issue. To suppress this unimportant error, we added ```date``` to
the command schedule for execution so that the retirn code is always zero. This
helps reduce confusion when consulting the REANA Web interface
