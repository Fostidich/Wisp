We have six different inputs:
1. provider
2. username
3. key
4. token
5. updates
6. hash mask

```
// input hash
list hashes <- get SHA256 bit string of provider, username, key, token

// updates shifts
int shifts = 0
for str in hashes
    shift_right(str, const(4)*shifts*updates)
    shifts++
    
// strings interweaving
init string plot with len 1024
for pos from 255 to 0
    plot[4*pos+3] = hashes.get(0)[pos]
    plot[4*pos+2] = hashes.get(1)[pos]
    plot[4*pos+1] = hashes.get(2)[pos]
    plot[4*pos+0] = hashes.get(3)[pos]
    
// convert plot to hash with hash mask
int word_size = 1024 / hash_mask.len()
init string result with len hash_mask.len()
for pos from 0 to hash_mask.len()
    string temp = string_section(plot, word_size*pos, word_size*pos+word_size)
    result[pos] = mask_to_char(hash_mask[pos], temp)

// finish
return result
```