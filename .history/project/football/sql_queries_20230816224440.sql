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
    player TEXT NOT NULL,
    price REAL NOT NULL
)