// This is a "stub" file.  It's a little start on your solution.
// It's not a complete solution though; you have to write some code.

// Package bob should have a package comment that summarizes what it's about.
// https://golang.org/doc/effective_go.html#commentary
package bob

import (
	"strings"
	"unicode"
)

func endsWithDot(remark string) bool {
	return strings.HasSuffix(remark, ".")
}

func endsWithExclamation(remark string) bool {
	return strings.HasSuffix(remark, "!")
}

func isInterrogation(remark string) bool {
	return strings.HasSuffix(remark, "?")
}

func hasNumbers(remark string) bool {
	return strings.IndexFunc(remark, unicode.IsNumber) > -1
}

func hasLetters(remark string) bool {
	return strings.IndexFunc(remark, unicode.IsLetter) > -1
}

func hasPunct(remark string) bool {
	return strings.IndexFunc(remark, unicode.IsPunct) > -1
}

func isShouting(remark string) bool {
	return strings.ToUpper(remark) == remark
}

func isForcefulQuestion(remark string) bool {
	return isAskingAQuestion(remark) && isShouting(remark)
}

func isAskingANumericQuestion(remark string) bool {
	return isAskingAQuestion(remark) && hasNumbers(remark)
}

func isShoutingNumbers(remark string) bool {
	return isShouting(remark) && hasNumbers(remark)
}

// Hey should have a comment documenting it.
func Hey(remark string) string {
	// Write some code here to pass the test suite.
	// Then remove all the stock comments.
	// They're here to help you get started but they only clutter a finished solution.
	// If you leave them in, reviewers may protest!

	r := strings.Trim(remark, " ")

	return ""
}
