# Mailmerge

#### Goal

In this assignment you are asked to design a mail merge program. “Mail merge is a process to
create personalized letters and pre-addressed envelopes or mailing labels for mass mailings from
a form letter” [1]. Feature works on a document that contains fixed text (that is same in each
output document) and variables (which act as placeholders that are replaced by text from the data
source).

#### Scenario and Implementation Requirements

Program will take the template and variable files as input, replace each placeholder with the
corresponding value from the variable file for each student and output each to a file named as the
value of the id and with a fixed extension “txt”. (Example: 2008900.txt) So for sure variables file
will have an attribute or element named “id” for each object, and you do not need to check the
existence of it. Examples input files are given below.

![Screenshot](https://github.com/ZagorTenay/Mailmerge/blob/master/ss1.JPG)

![Screenshot](https://github.com/ZagorTenay/Mailmerge/blob/master/ss2.JPG)

Be careful about the following scenarios:

  1. Scenario: Template file have a placeholder that does not exist in variables file.

  Action: If not all placeholders exist in variables file that record/object will be ignored and
no output will be given for it.

  2. Scenario: Variables file have extra elements that the template file does not have
placeholder for.

  Action: Output the related record/object as normal, just omit the extra element.
Your program will take exactly and only three arguments on any order. These are arguments
are:

   1. The template file that contains the fixed text and placeholders for variables. This
argument will be given with the flag “-t” and it can be a single file name as well as the
filename with preceding path.

    Example: <-t template.xml> or <-t /home/user/Desktop/Assignment1/template.xml>

   2. The variables file to replace the corresponding placeholders with. This argument will be
given with the flag “-v” and it can be a single file name as well as the filename with
preceding path.

    Example: <-v variables.xml> or <-v ../Desktop/variables.xml>

   3. The folder for outputting the created documents. This argument will be given with the flag
“-o” and it can be a single folder name as well as the folder name with preceding path.

    Example: <-o outputs> or <-o ./TestCase1/outputs>

Usage of your program is to be exactly as (arguments may change ofcourse):

    ./mm –t tamplate.xml –v variables.xml –o ../outputs/testcase1
