Feature: Example of game story feature

Scenario: I want to test the homepage
Given I am on the dashboard
When I click homepage button
And wait for 5 seconds
And don't press anything
Then the homepage will appear
