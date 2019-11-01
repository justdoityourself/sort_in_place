# sort_in_place
C++ template library that sorts data byte by byte by building a tree of segment-pointers instead of hard copying data into the tree.

## Concept:

Using segments and targeting a known and fixed block size, we can find an optimal representation of the block for compression purposes.

## TODO
* Transform the tree into a bitstream.
* Benchmark and compare performance and compression ratio.