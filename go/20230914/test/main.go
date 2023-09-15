package main

import (
	"fmt"
	"time"
)

type User struct {
}

func main() {
	// demo1("abcd")
	// demo2()
	// demo3()
	var u *User
	fmt.Printf("u: %v\n", u)
	u = new(User)
	fmt.Printf("u: %v\n", u)
}

func demo1(s string) {
	len := len(s)
	str := make([]byte, len)
	for i := 0; i < len; i++ {
		str[i] = s[len-i-1]
	}
	fmt.Println(string(str))
}

func demo2() {
	arr := []int{1, 2, 3, 4, 5, 6}
	for _, v := range arr {
		go func(n int) {
			fmt.Println(n)
		}(v)
	}
}

func demo3() {
	arr := []int{1, 2, 3, 4, 5, 6}
	for _, v := range arr {
		go func(n int) {
			fmt.Println(v)
		}(v)
		time.Sleep(time.Second)
	}
}
