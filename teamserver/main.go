package main

import "Catedral/cmd"
import "Catedral/pkg/logger"

func main() {
	err := cmd.CatedralCli.Execute()
	if err != nil {
		logger.Error("Failed to execute catedral")
		return
	}
}
