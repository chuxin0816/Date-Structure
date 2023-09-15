package main

import "fmt"

type List struct {
	date int
	next *List
}

var head *List

func main() {
	head = &List{date: 0, next: nil}
	var n int
	fmt.Scan(&n)
	for i := 1; i <= n; i++ {
		var a int
		fmt.Scan(&a)
		head.insert(a, i)
	}
	head.show()
	for i := 0; i < 2; i++ {
		var pa, pb int
		fmt.Scan(&pa, &pb)
		if ok := head.swap(pa, pb); ok {
			head.show()
		} else {
			fmt.Println("error")
		}
	}
}

func (l *List) swap(pa, pb int) bool {
	if pa < 1 || pb < 1 {
		return false
	}
	tmp1, tmp2 := head, head
	for i := 1; i < pa; i++ {
		tmp1 = tmp1.next
		if tmp1 == nil {
			return false
		}
	}
	for i := 1; i < pb; i++ {
		tmp2 = tmp2.next
		if tmp2 == nil {
			return false
		}
	}
	if tmp1.next == nil || tmp2.next == nil {
		return false
	}
	if tmp1.next.next == nil || tmp2.next.next == nil {
		return false
	}
	tmp1.next.next, tmp2.next.next = tmp2.next.next, tmp1.next.next
	tmp1.next, tmp2.next = tmp2.next, tmp1.next
	return true
}

func (l *List) insert(date int, pos int) bool {
	if pos < 1 {
		return false
	}
	tmp := head
	node := &List{date: date, next: nil}
	for i := 1; i < pos; i++ {
		tmp = tmp.next
		if tmp == nil {
			return false
		}
	}
	node.next = tmp.next
	tmp.next = node
	return true
}

func (l *List) show() {
	tmp := head.next
	for tmp != nil {
		fmt.Printf("%d ", tmp.date)
		tmp = tmp.next
	}
	fmt.Println()
}
