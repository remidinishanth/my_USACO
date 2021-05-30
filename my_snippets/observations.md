* Whenever you see, there is atleast `⌈N/2⌉` or `⌈N/3⌉` elements in the answer, see if you can use randomization. Say we need to have atleast `⌈N/2⌉` elements in the answer, if we choose a person at random, there is half probability that element is in the answer. So if we repeat this process say 30 times, then the probability of failure reduces to `(1/2)^30`. Hence this works most of the time.
  * Problem: https://codeforces.com/contest/1523/problem/D , Solution: https://codeforces.com/contest/1523/submission/117881477
  ![image](https://user-images.githubusercontent.com/19663316/120113940-6f380a00-c19a-11eb-8a77-b3c4c761a32d.png)

