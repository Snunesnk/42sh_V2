# Job Module

Module "job" handles the execution of commands.
Thereby, it checks if access to the cmd is possible, access(), builtins and then fork it or return an error msg.
On call of the module execute one command with its options.
to call the module -> job(char** argv, char **envip), it returns the return value of the execute command. In case command is not found it returns the value defined by the enum. e.g "command not found = 127"



#### int check_access(char **arg)

Concat path in order to find the binary
*F_OK*
>    Tests whether the file exists.
*X_OK*
>    Tests whether the file can be accessed for executio


## Flowchart
![Job Module Flowchart](../../tools/flowcharts/job_flowchart.png)
