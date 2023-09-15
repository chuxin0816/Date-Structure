package main

import (
	"fmt"
)

type List struct {
	num  int
	name string
	next *List
}

func main() {
	free := &List{num: 0, name: "", next: nil} //可用
	used := &List{num: 0, name: "", next: nil} //已用
	var n, m int
	fmt.Scan(&n)
	stu := make(map[int]string)
	for i := 0; i < n; i++ {
		var name string
		var num int
		fmt.Scan(&name, &num)
		stu[num] = name
	}
	for i := 101; i <= 120; i++ {
		name := stu[i]
		if name == "" {
			free.push_back(i, stu[i])
		} else {
			used.push_back(i, stu[i])
		}
	}
	fmt.Scan(&m)
	for i := 0; i < m; i++ {
		var op string
		fmt.Scan(&op)
		switch op {
		case "assign":
			{
				var name string
				fmt.Scan(&name)
				num := free.pop_head()
				used.insert(num, name)
			}
		case "return":
			{
				var num int
				fmt.Scan(&num)
				used.del(num)
				free.push_back(num, "")
			}
		case "display_free":
			{
				free.display_free()
			}
		case "display_used":
			{
				used.display_used()
			}
		}
	}
}

func (l *List) push_back(num int, name string) {
	tmp := l
	node := &List{num: num, name: name, next: nil}
	for tmp.next != nil {
		tmp = tmp.next
	}
	tmp.next = node
}

func (l *List) pop_head() int {
	tmp := l.next.num
	l.next = l.next.next
	return tmp
}

func (l *List) insert(num int, name string) {
	node := &List{num: num, name: name, next: nil}
	tmp := l
	if num < tmp.next.num {
		node.next = tmp.next
		tmp.next = node
		return
	}
	for tmp.next != nil {
		if tmp.next.num < num {
			tmp = tmp.next
		} else {
			node.next = tmp.next
			tmp.next = node
			return
		}
	}
	tmp.next = node
}

func (l *List) del(num int) {
	tmp := l
	for tmp.next != nil {
		if tmp.next.num == num {
			tmp.next = tmp.next.next
			return
		}
		tmp = tmp.next
	}
}

func (l *List) display_used() {
	tmp := l.next
	for tmp.next != nil {
		fmt.Printf("%s(%d)-", tmp.name, tmp.num)
		tmp = tmp.next
	}
	fmt.Printf("%s(%d)\n", tmp.name, tmp.num)
}

func (l *List) display_free() {
	tmp := l.next
	for tmp.next != nil {
		fmt.Printf("%d-", tmp.num)
		tmp = tmp.next
	}
	fmt.Println(tmp.num)
}
