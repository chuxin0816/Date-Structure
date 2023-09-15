package main

import "fmt"

type List struct {
	c, i int
	next *List
}

var head1, head2, head3 *List

func main() {
	var t, n int
	fmt.Scan(&t)
	for i := 0; i < t; i++ {
		head1 := &List{c: 0, i: 0, next: nil}
		head2 := &List{c: 0, i: 0, next: nil}
		head3 := &List{c: 0, i: 0, next: nil}
		fmt.Scan(&n)
		for j := 1; j <= n; j++ {
			var c, in int
			fmt.Scan(&c, &in)
			head1.insert(c, in, j)
		}
		fmt.Scan(&n)
		for j := 1; j <= n; j++ {
			var c, in int
			fmt.Scan(&c, &in)
			head2.insert(c, in, j)
		}
		head3.add(head1, head2)
		head1.show()
		head2.show()
		head3.show()
	}
	fmt.Println()
}

func (l *List) insert(c, i, pos int) {
	tmp := l
	node := &List{c: c, i: i, next: nil}
	for i := 1; i < pos; i++ {
		tmp = tmp.next
	}
	node.next = tmp.next
	tmp.next = node
}

func (l *List) show() {
	tmp := l.next
	first := true
	for tmp != nil {
		if tmp.c == 0 {
			tmp = tmp.next
			continue
		} else {
			if !first {
				fmt.Print(" + ")
			} else {
				if tmp.c != 0 {
					first = false
				}
			}
		}
		if tmp.c < 0 {
			fmt.Printf("(%d)", tmp.c)
		} else {
			fmt.Printf("%d", tmp.c)
		}
		if tmp.i != 0 {
			if tmp.i < 0 {
				fmt.Printf("x^(%d)", tmp.i)
			} else {
				fmt.Printf("x^%d", tmp.i)
			}
		}
		if tmp.next != nil {
			tmp = tmp.next
		} else {
			fmt.Println()
			break
		}
	}
}

func (l *List) add(l1, l2 *List) {
	tmp1 := l1.next
	tmp2 := l2.next
	pos := 1
	for tmp1 != nil && tmp2 != nil {
		if tmp1.i == tmp2.i {
			l.insert(tmp1.c+tmp2.c, tmp1.i, pos)
			tmp1 = tmp1.next
			tmp2 = tmp2.next
			pos++
		} else if tmp1.i < tmp2.i {
			l.insert(tmp1.c, tmp1.i, pos)
			tmp1 = tmp1.next
			pos++
		} else {
			l.insert(tmp2.c, tmp2.i, pos)
			tmp2 = tmp2.next
			pos++
		}
	}
	for tmp1 != nil {
		l.insert(tmp1.c, tmp1.i, pos)
		tmp1 = tmp1.next
		pos++
	}
	for tmp2 != nil {
		l.insert(tmp2.c, tmp2.i, pos)
		tmp2 = tmp2.next
		pos++
	}
}
