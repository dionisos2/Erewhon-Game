Database = {
	Host = "localhost",
	Port = 5432,
	Name = "erewhon",
	Username = "erewhon",
	Password = "erewhon",
	WorkerCount = 2
}

Game = {
	MaxClients = 100,
	Port       = 2050
}

-- Warning: changing these parameters will break login to already registered accounts
Security = {
	PasswordSalt = "<randomsalt>",
}
