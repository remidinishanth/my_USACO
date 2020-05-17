// Think Binary search as prefix of False and suffix of True or the
// other way around, then you are asked to find the boundary that is the 
// first True or the first False

// Look at the middle answer, if it is satisfied go to a possible better
// answer, otherwise go to a half containing answer.

void binary_search(){
	L=0, R=N-1;
	while L <=R :
		mid = L + (R-L)/2
		if a[mid]==target:
			return mid
		if a[mid]<target:
			L=mid+1
		else:
			R=mid-1
	return -1
}

void lower_bound(){
	L=0,R=N-1;
	ans=-1;
	while L<=R:
		mid=L+(R-L)/2
		if a[mid]>=target:
			// better values to the leftmost
			ans=mid // a[mid]
			R=mid-1 // look for better values
		else:
			L=mid+1
	return ans
}


// Problem:
// You have a function f in an interval [a,b] of real numbers, and you want to find the x for which 
// f(x) is maximized. You know that the function f is unimodal: it is strictly increasing in the 
// interval [a,x], and strictly decreasing in the interval [x,b].

// Solution:
// If we are working with an interval of integers, not an interval of reals, simply use binary search 
// (see "binary search" recipe). (The property P(x) we are working with is the following one: f(x) > f(x+1).)

// For reals, use the following algorithm, known as ternary search:
double l = a, r = b;
 
for(int i=0; i<200; i++) {
  double l1 = (l*2+r)/3;
  double l2 = (l+2*r)/3;
  if(f(l1) > f(l2)) r = l2; else l = l1;
  }
 
x = l;
