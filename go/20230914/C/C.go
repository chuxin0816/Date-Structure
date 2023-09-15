package main

import "fmt"

type List struct {
	date int
	next *List
}

var head1, head2, head3 *List

func main() {
	head1 := &List{date: 0, next: nil}
	head2 := &List{date: 0, next: nil}
	head3 := &List{date: 0, next: nil}
	var n, m int
	fmt.Scan(&n)
	for i := 1; i <= n; i++ {
		var a int
		fmt.Scan(&a)
		head1.insert(a, i)
	}
	fmt.Scan(&m)
	for i := 1; i <= m; i++ {
		var a int
		fmt.Scan(&a)
		head2.insert(a, i)
	}
	pos := 1
	tmp1 := head1.next
	tmp2 := head2.next
	for {
		if tmp1 == nil || tmp2 == nil {
			break
		}
		if tmp1.date < tmp2.date {
			head3.insert(tmp1.date, pos)
			tmp1 = tmp1.next
			pos++
		} else {
			head3.insert(tmp2.date, pos)
			tmp2 = tmp2.next
			pos++
		}
	}
	for tmp1 != nil {
		head3.insert(tmp1.date, pos)
		tmp1 = tmp1.next
		pos++
	}
	for tmp2 != nil {
		head3.insert(tmp2.date, pos)
		tmp2 = tmp2.next
		pos++
	}
	head3.show()
}
func (l *List) insert(date int, pos int) bool {
	if pos < 1 {
		return false
	}
	tmp := l
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
	tmp := l.next
	for tmp != nil {
		fmt.Printf("%d ", tmp.date)
		tmp = tmp.next
	}
	fmt.Println()
}
