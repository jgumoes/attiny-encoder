# Timings

there's an issue that sometimes happens, where the counts can underflow to UINT16_MAX, even though there are guard closes preventing the counts from decrementing if the count is 0. i think more guard clauses might help, i.e.

```c++
int8_t count = 69;

...

if(count > 0){
  // do stuff
}
else{
  count = 0;
}
```

But, I want to speed things up before I add the extra processing.

## Attempts

### 0 encoder rotation speed

the fastest I can spin it is 1.3 mS for a full cycles, or 325 uS per pulse. so 3 KHz data input rate

### 1 original attempt

output pulses are 130 uS wide, so 260 uS per rotation tick. only 3.8 kHz, but fast enough that single-byte counts shouldn't overflow. still way lower than the 400 KHz the clock is set to, which should result in 1.25 uS pulse widths.

### 2 changing the count

count = 1 => 127 uS per pulse
count = 5 => 130 uS per pulse
count = 10 => 130 uS per pulse

*note: i only measured one pulse that seemed large.*

the timer is basically irrelavant, it's the code that's slow

### 3 change the count type

changed the 16 bit counts to unsigned 8 bit counts, with a count of 10. pulse width went to 75 uS.

Also, build size went up by 2 bytes. It doesn't matter, but still, WTF?

### 4 remove the update methods

removed all the update methods by folding them into the switch-case. also removed the nested if's by folding them into cases. got 86 uS per pulse, or 5.8 KHz data output.

### 5 seperate increments to seperate methods

I removed the guard clauses nested in the switch-case and seperated them to seperate methods. the build size went up to 438 bytes, and the pulse time went to 117 uS.

*hmm.*

### 6 two big if statements

if clockwise state, increment clockwise. if anticlockwise state, increment anticlockwise. build size is now 396 bytes, but pulse width is 96 clockwise, and 99 uS anticlockwise (guess which if came first?).

### 7 remove the object

destruct the StateMachine object into a namespace. build size is now 458 bytes, but pulse width is 78 uS (which is what actually matters).

Clearly, bigger build size is better, and this definitaley applies to all languages and all contexts.

### 8 Guards! Guards!

added the extra guard. pulse width is 107 uS, for 4.7 kHz data output.

### 9 lets get shifty!

shift the bits in take() instead of shifting the result. took 108 uS, probably because instead of one shift there are now two.

### 10 it's looking a bit *too* shifty

pre-shift the bits in take. pulse width is 109 uS, so no improvement.

## Conclusion

Number 8 seams to work, I haven't managed to make it underflow at all and the data out rate is high enough that the counts shouldn't exceed one.
