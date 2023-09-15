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
		var pos, date int
		fmt.Scan(&pos, &date)
		if ok := head.insert(date, pos); ok {
			head.show()
		} else {
			fmt.Println("error")
		}
	}
	for i := 0; i < 2; i++ {
		var pos int
		fmt.Scan(&pos)
		if ok := head.del(pos); ok {
			head.show()
		} else {
			fmt.Println("error")
		}
	}
	for i := 0; i < 2; i++ {
		var pos int
		fmt.Scan(&pos)
		if date, ok := head.find(pos); ok {
			fmt.Println(date)
		} else {
			fmt.Println("error")
		}
	}
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

func (l *List) del(pos int) bool {
	if pos < 1 {
		return false
	}
	tmp := head
	for i := 1; i < pos; i++ {
		tmp = tmp.next
		if tmp == nil {
			return false
		}
	}
	tmp.next = tmp.next.next
	return true
}

func (l *List) find(pos int) (int, bool) {
	if pos < 1 {
		return 0, false
	}
	tmp := head.next
	for i := 1; i < pos; i++ {
		tmp = tmp.next
		if tmp == nil {
			return 0, false
		}
	}
	return tmp.date, true
}

func (l *List) show() {
	tmp := head.next
	for tmp.next != nil {
		fmt.Printf("%d ", tmp.date)
		tmp = tmp.next
	}
	fmt.Printf("%d \n", tmp.date)
}
