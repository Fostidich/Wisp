We have six different inputs:
1. provider
2. username
3. key
4. token
5. update
6. hash mask

### General algorithm:
```
// input hash
init list hashes <- SHA256 of provider, username, key, token

// update shifts
shifts = 0
for str in hashes
    shift_right(str, const(4)*shifts*update)
    shifts++
    
// input hashes xor
init plot <- hashes[0]
for i from 1 to 4
    plot = plot xor hashes[i]   
    
// convert plot to hash with hash mask
satisfy hash mask constraints
init temp2, temp <- plot
for char in hash mask
    temp2 <- SHA256 of temp
    num <- byte xor of temp2
    result->add(num)
    temp <- temp2
    
// finish
print hashMask->assign(result)
```
