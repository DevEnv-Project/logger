# logger
A simple single-file C++ logger

## Usage
Simply copy the file into your project.

The namespace for this is called `Logger`.
There are a number of versions of this.

- `logger_basic.hpp`: A basic logger, no tracing, literally just a date, time, and formatted text. This version does not include an option to write to a stream, just `stdout`
- `logger_trace.hpp`: A slightly more complex logger, with a built in FN1A64 hashing algorithm for generating traces
- `logger_section.hpp`: More details! This version comes with everything, then a little `section` string