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