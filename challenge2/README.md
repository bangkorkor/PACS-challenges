# Challenges 2 

### A Spare Matrix 

It is often necessary to exploit sparsity to be able to operate with large matrices. We also want a reader of matrices written on *Matrix Market Form*. See [pdf](https://github.com/bangkorkor/PACS-challenges/blob/main/challenge2/doc/Challenge23-24-2.pdf) for documentation.



### To run code 

No external libaries needed, just navigate to the challenge2 directory and do ```make``` to compile. 
Do ```./build/main``` to execute


### Results 

When running the test_time_RowMajor and test_time_ColumnMajor functions one can clearly see that the run time is quicker when the matix is compressed rather then uncompressed, around 60% quicker. 

# Remarks

### Dynamic vs compressed

I think i have misunderstoop what compressed and uncompressed matricies are, therefore when the matrix is compressed it is actually on COO form, which is uncompressed in regard to the challenge-description. When my matrix is uncompressed, zero-elements also are initialized. When I call the compressCOO() function, only non-zero elements are kept in the map. This still makes the matrix-vector multiplication faster. 

### () operator

When adding values to the matrix you use the () operator. When trying to add values out of bounds nothing happends. You can add new values (in bounds) in uncompressed state, but in compressed state you can only change existing ones.


### Resize

You can resize matrices in compressed and uncompressed state. You can make matrices larger, and the new places will be initialized with zeros. You can make matrices smaller and the deleted places will get lost. After resizing the matrix will always be in uncompressed state.

