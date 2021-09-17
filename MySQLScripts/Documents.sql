CREATE TABLE Crawler.Documents (
	id INT NULL AUTO_INCREMENT,
	url VARCHAR(256) UNIQUE NOT NULL,
	title varchar(10000) NOT NULL,
	description LONGTEXT NOT NULL,
	content LONGTEXT NOT NULL,
	PRIMARY KEY(id),
	FULLTEXT(title, description, content)
)
