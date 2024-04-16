# Challenges 2 - A sparse matrix #

## To run code 

No external libaries needed, just navigate to the challenge2 directory and do ```make``` to compile. 
Do ```./build/main``` to execute


## Remarks about functions 

### () operator

When adding values to the matrix you use the () operator. When trying to add values out of bounds nothing happends. You can add new values (in bounds) in uncompressed state, but in compressed state you can only change existing ones.


### Resize

You can resize matrices in compressed and uncompressed state. You can make matrices larger, and the new places will be initialized with zeros. You can make matrices smaller and the deleted places will get lost. After resizing the matrix will always be in uncompressed state.

