CREATE TRIGGER update_action
AFTER INSERT ON transactions
FOR EACH ROW
BEGIN
    UPDATE transactions
    SET action = CASE
        WHEN NEW.shares > 0 THEN 'Bought'
        WHEN NEW.shares < 0 THEN 'Sold'
        ELSE 'Other'
    END
    WHERE id = NEW.id;
    

CREATE TABLE transactions (
    id INTEGER PRIMARY KEY NOT NULL,
    player_id INTEGER NOT NULL,
    price REAL NOT NULL
);

CREATE TABLE players (
    id INTEGER PRIMARY KEY NOT NULL,
    first_name TEXT NOT NULL,
    last_name text NOT NULL,
    value 
)