# CLTE
C++ &amp; Lua Template Engine

## How does it work?

There are two files needed, one data file and one template file. The data file
should be in YAML or JSON, the template file is copied to the output file,
recognizing the following tags:

* `@#` Comment tag. Removes anything from the output until the end of the
  line, including the newline. This means it can also be used to escape
  newlines, like M4's `dnl`. Needs no end tags.
* `@.` Expression end tag to denote the end of another tag containing an
  expression.
* `@;` Block end tag to denote a block end following a conditional tag.
* `@=` Output expression tag. Outputs the result of the Lua expression directly following it, until the end tag.
* `@!` Execution tag. Execute the Lua code following this tag, but don't
  output anything directly. Needs a block end tag.
* `@?` If the following expression results to true, continue processing the template
  until the block end tag. Translates to a Lua `if` statement.
* `@:` Translates to a Lua `else` tag.
* `@$` Processing iterations tag to iterate over a dictionary, list or array
  from the data file. Requires both the expression end and block end tag.
* `@^` Represents the key of the inner-most processing block being iterated.
* `@^^` Represents the key of the second inner-most processing block being iterated.
* `@^^^` Represents the key of the third inner-most processing block being iterated,
  etc.
* `@+` Represents value of the inner-most processing block being iterated.
* `@++` Represents value of the second inner-most processing block being iterated.
* `@+++` Represents value of the third inner-most processing block being iterated, etc.

## Why create *another* template engine?

This application was create with code generation in mind for software
projects, generating C++, Slice definitions, SQL and alike. There are already
various template engines out there. However, I've found that they don't meet
my needs, because of the following reasons found below.

* *Most of them are focussed on web applications* This means they have all
  kinds of "smartness" for escaping HTML, which is only annoying for other
  types of code.
* *They use scripting languages* like Ruby, JavaScript, Python and what not.
  When generating code, it should be fast, efficient and with a small
  footprint in the development environment. Why bother with scripting
  languages for a task that is relatively simple and straightforward? It is
  again a clear choice made towards what developers are *familiar* with
  instead of choosing the *right tool for the right job*.
* *Processing posibilities are too simple* like in Jinja2 or the
  self-proclaimed "logic-less" Mustache. I want to have ample flexibility to
  write some code in my templates, not be limited by what the template engine
  can or can't do.
