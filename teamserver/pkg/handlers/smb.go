package handlers

import (
    "Catedral/pkg/colors"
    "Catedral/pkg/logger"
)

func NewPivotSmb() *SMB {
    var Smb = new(SMB)

    return Smb
}

func (s *SMB) Start() {
    logger.Info("Started \"" + colors.Green(s.Config.Name) + "\" listener")

    pk := s.Teamserver.ListenerAdd("", LISTENER_PIVOT_SMB, s)
    s.Teamserver.EventAppend(pk)
    s.Teamserver.EventBroadcast("", pk)
}
