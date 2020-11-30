# Mr-Worldwide

**View full writeup:** https://jasonturley.xyz/picoctf-2019-mr-worldwide-writeup/

## Description
> A musician left us a message. What's it mean?

**Points:** 200

## Solution
We are given a message with several coordinates. Plug them into Google Maps and
use the first letter of each city as a character in the flag.

```
(35.028309, 135.753082)  [K]yoto
(46.469391, 30.740883)   [O]desa
(39.758949, -84.191605)  [D]ayton
(41.015137, 28.979530)   [I]nstanbul
(24.466667, 54.366669)   [A]bu Dhabi
(3.140853, 101.693207)   [K]uala Lumpur
_
(9.005401, 38.763611)    [A]ddis Ababa
(-3.989038, -79.203560)  [L]oja
(52.377956, 4.897070)    [A]msterdam
(41.085651, -73.858467)  [S]leepy Hallow
(57.790001, -152.407227) [K]odiak
(31.205753, 29.924526)   [A]lexandria
```
The flag is picoCTF{KODIAK_ALASKA}
