#pragma once

class Score
{
public:
	Score(void);
	~Score(void);

	void computeScore();

private:
	double p1Score, p2Score;
};

