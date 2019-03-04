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

Example template file: template.xml
