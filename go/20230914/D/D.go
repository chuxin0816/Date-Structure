package main

import (
	"fmt"
)

type List struct {
	date int
	next *List
}

func main() {
	var n, k, s int
	for {
		_, err := fmt.Scan(&n, &k, &s)
		if err != nil {
			break
		}
		head := &List{date: n, next: nil}
		for i := 1; i < n; i++ {
			head.insert(i, i)
		}
		tmp := head
		for i := 1; i < n; i++ {
			tmp = tmp.next
		}
		tmp.next = head
		for i := 1; i <= s; i++ {
			head = head.next
		}
		for {
			if head.next == head {
				fmt.Printf("%d \n", head.date)
				break
			}
			for i := 1; i < k-1; i++ {
				head = head.next
			}
			head.del(1)
			head = head.next
		}
	}
}

func (l *List) insert(date int, pos int) {
	tmp := l
	node := &List{date: date, next: nil}
	for i := 1; i < pos; i++ {
		tmp = tmp.next
	}
	node.next = tmp.next
	tmp.next = node
}

func (l *List) del(pos int) { //删除后面的第pos个节点
	tmp := l
	for i := 1; i < pos; i++ {
		tmp = tmp.next
	}
	fmt.Printf("%d ", tmp.next.date)
	tmp.next = tmp.next.next
}
